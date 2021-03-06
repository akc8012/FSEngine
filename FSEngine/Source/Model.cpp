#include "..\Header\Model.h"

Model::Model()
{
	meshComponents = make_unique<ComponentCollection<Mesh>>();
	textureComponents = make_unique<ComponentCollection<Texture>>();
}

Model::Model(const string& filepath)
{
	meshComponents = make_unique<ComponentCollection<Mesh>>();
	textureComponents = make_unique<ComponentCollection<Texture>>();

	Load(filepath);
}

void Model::Load(const string& filepath)
{
	this->filepath = filepath;
	meshComponents->Clear();
	textureComponents->Clear();

	unique_ptr<Importer> importer = LoadModelImporter(filepath.c_str());
	const aiScene* scene = importer->GetScene();

	ConvertMeshesOnNode(scene->mRootNode, scene);
}

unique_ptr<Importer> Model::LoadModelImporter(const string& filepath)
{
	unique_ptr<Importer> importer(new Importer());
	const aiScene* scene = importer->ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
		throwFS("Assimp error: " + (string)(importer->GetErrorString()));

	return importer;
}

void Model::ConvertMeshesOnNode(const aiNode* node, const aiScene* scene)
{
	for (Uint32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		shared_ptr<Mesh> meshComponent = ConvertMeshToComponent(mesh);
		meshComponents->Add(meshComponent, mesh->mName.C_Str());

		bool hasMaterials = mesh->mMaterialIndex >= 0;
		if (hasMaterials)
			ConvertMaterialToTextures(meshComponent.get(), scene->mMaterials[mesh->mMaterialIndex]);
	}

	for (Uint32 i = 0; i < node->mNumChildren; i++)
		ConvertMeshesOnNode(node->mChildren[i], scene);
}

shared_ptr<Mesh> Model::ConvertMeshToComponent(const aiMesh* mesh)
{
	vector<vertex> vertices = ConvertVertices(mesh);
	vector<Uint32> indices = ConvertIndices(mesh);

	return make_shared<Mesh>(vertices, indices);
}

vector<vertex> Model::ConvertVertices(const aiMesh* mesh)
{
	vector<vertex> vertices;
	for (Uint32 i = 0; i < mesh->mNumVertices; i++)
	{
		vertex vertex;
		vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		bool hasTextureCoords = mesh->mTextureCoords[0];
		vertex.textureCoord = hasTextureCoords ? vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : vec2(0, 0);

		vertices.push_back(vertex);
	}

	return vertices;
}

vector<Uint32> Model::ConvertIndices(const aiMesh* mesh)
{
	vector<Uint32> indices;
	for (Uint32 faceNdx = 0; faceNdx < mesh->mNumFaces; faceNdx++)
	{
		aiFace face = mesh->mFaces[faceNdx];

		for (Uint32 indexNdx = 0; indexNdx < face.mNumIndices; indexNdx++)
			indices.push_back(face.mIndices[indexNdx]);
	}

	return indices;
}

void Model::ConvertMaterialToTextures(Mesh* meshComponent, const aiMaterial* material)
{
	const aiTextureType textureType = aiTextureType_DIFFUSE;
	for (Uint32 i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString textureFileName;
		material->GetTexture(textureType, i, &textureFileName);

		AddTextureComponent(meshComponent, textureFileName.C_Str());
	}
}

void Model::AddTextureComponent(Mesh* meshComponent, const string& textureName)
{
	unique_ptr<string> loadedTextureName(TryGetLoadedTextureName(textureName));
	if (loadedTextureName == nullptr)
	{
		meshComponent->SetShadingName(textureName);
		textureComponents->Add(make_shared<Texture>(GetDirectory() + textureName), textureName);
	}
	else
		meshComponent->SetShadingName(*loadedTextureName);
}

string* Model::TryGetLoadedTextureName(const string& textureName) const
{
	for (const auto texture : textureComponents->GetComponents())
	{
		string loadedTextureName = texture->GetName();
		if (textureName == loadedTextureName)
			return new string(loadedTextureName);
	}

	return nullptr;
}

string Model::GetDirectory() const
{
	return filepath.substr(0, filepath.find_last_of('/')+1);
}

ComponentCollection<Mesh>* Model::GetMeshCollection() const
{
	return meshComponents.get();
}

ComponentCollection<Texture>* Model::GetTextureCollection() const
{
	return textureComponents.get();
}

json Model::GetJson() const
{
	json j = Component::GetJson();
	j["Filepath"] = filepath;
	return j;
}

void Model::SetFromJson(const json& j)
{
	Component::SetFromJson(j);

	string jsonFilepath = j["Filepath"].get<string>();
	if (jsonFilepath != filepath)
		Load(jsonFilepath);
}

Types::ComponentType Model::GetComponentTypeId() const
{
	return ComponentTypeId;
}
