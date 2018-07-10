#include "..\Header\Model.h"

Model::Model(const string& filepath)
{
	this->directory = filepath.substr(0, filepath.find_last_of('/')+1);

	unique_ptr<Importer> importer = LoadModelImporter(filepath.c_str());
	const aiScene* scene = importer->GetScene();

	ConvertMeshesOnNode(scene->mRootNode, scene);
}

unique_ptr<Importer> Model::LoadModelImporter(const char* filepath)
{
	unique_ptr<Importer> importer(new Importer());
	const aiScene* scene = importer->ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
		throw "Assimp error: " + (string)(importer->GetErrorString());

	return importer;
}

void Model::ConvertMeshesOnNode(const aiNode* node, const aiScene* scene)
{
	for (Uint32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshComponents.push_back(ConvertMeshToComponent(mesh));

		bool hasMaterials = mesh->mMaterialIndex >= 0;
		if (hasMaterials)
		{
			const int MeshIndex = (int)meshComponents.size() - 1;
			vector<tuple<Uint32, TextureComponent*>> textures = ConvertMaterialToTextures(MeshIndex, scene->mMaterials[mesh->mMaterialIndex]);
			textureComponents.insert(textureComponents.begin(), textures.begin(), textures.end());
		}
	}

	for (Uint32 i = 0; i < node->mNumChildren; i++)
		ConvertMeshesOnNode(node->mChildren[i], scene);
}

MeshComponent* Model::ConvertMeshToComponent(const aiMesh* mesh)
{
	vector<Vertex> vertices = ConvertVertices(mesh);
	vector<Uint32> indices = ConvertIndices(mesh);

	return new MeshComponent(vertices, indices);
}

vector<tuple<Uint32, TextureComponent*>> Model::ConvertMaterialToTextures(int meshIndex, const aiMaterial* material)
{
	vector<tuple<Uint32, TextureComponent*>> textures;

	vector<TextureComponent*> diffuseTextures = ConvertTextures(material, aiTextureType_DIFFUSE);
	for (const auto& textureComponent : diffuseTextures)
	{
		textureComponent->SetTextureType(TextureComponent::Diffuse);
		textures.push_back(std::make_tuple(meshIndex, textureComponent));
	}

	return textures;
}

vector<Vertex> Model::ConvertVertices(const aiMesh* mesh)
{
	vector<Vertex> vertices;
	for (Uint32 i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
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

vector<TextureComponent*> Model::ConvertTextures(const aiMaterial* material, const aiTextureType& textureType)
{
	vector<TextureComponent*> textures;
	for (Uint32 i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString texturePath;
		material->GetTexture(textureType, i, &texturePath);

		TextureComponent* loadedTexture = FindAlreadyLoadedTexture((string)texturePath.C_Str());
		if (loadedTexture == nullptr)
			loadedTexture = new TextureComponent((directory + texturePath.C_Str()).c_str());

		textures.push_back(loadedTexture);
	}

	return textures;
}

TextureComponent* Model::FindAlreadyLoadedTexture(const string& texturePath) const
{
	for (const auto& textureComponent : textureComponents)
	{
		TextureComponent* loadedTexture = std::get<TextureIndex>(textureComponent);
		if (texturePath == loadedTexture->GetFilename())
			return loadedTexture;
	}

	return nullptr;
}

vector<MeshComponent*> Model::GetMeshComponents() const
{
	return meshComponents;
}

vector<tuple<Uint32, TextureComponent*>> Model::GetTextureComponents() const
{
	return textureComponents;
}

Model::~Model()
{
	for (auto& meshComponent : meshComponents)
		delete meshComponent;

	for (auto& textureComponent : textureComponents)
	{
		TextureComponent* texture = std::get<TextureIndex>(textureComponent);
		if (texture == nullptr)
			continue;

		delete texture;
		texture = nullptr;
	}
}
