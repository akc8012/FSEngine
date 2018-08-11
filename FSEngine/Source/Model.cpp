#include "..\Header\Model.h"

Model::Model(const string& filepath, FileSystem* fileSystem, Input* input, Window* window)
 : GameObject(fileSystem, input, window)
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
		MeshComponent* meshComponent = ConvertMeshToComponent(mesh);
		AddComponent(meshComponent, mesh->mName.C_Str());

		bool hasMaterials = mesh->mMaterialIndex >= 0;
		if (hasMaterials)
			ConvertMaterialToTextures(meshComponent, scene->mMaterials[mesh->mMaterialIndex]);
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

void Model::ConvertMaterialToTextures(MeshComponent* meshComponent, const aiMaterial* material)
{
	const aiTextureType textureType = aiTextureType_DIFFUSE;
	for (Uint32 i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString texturePath;
		material->GetTexture(textureType, i, &texturePath);

		string* loadedTextureName = GetLoadedTextureName((string)texturePath.C_Str());
		if (loadedTextureName == nullptr)
		{
			string textureName = texturePath.C_Str();
			meshComponent->AddAssociatedTextureName(textureName);

			AddComponent(new TextureComponent(directory + textureName, textureName), textureName);
		}
		else
		{
			meshComponent->AddAssociatedTextureName(*loadedTextureName);
			delete loadedTextureName;
		}
	}
}

string* Model::GetLoadedTextureName(const string& texturePath) const
{
	for (const auto& textureComponent : *GetComponents<ShadingComponent>())
	{
		string name = dynamic_cast<TextureComponent*>(textureComponent.second)->GetName();
		if (texturePath == name)
			return new string(name);
	}

	return nullptr;
}
