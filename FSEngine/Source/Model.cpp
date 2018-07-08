#include "..\Header\Model.h"

Model::Model(const string& filepath)
{
	const aiScene* scene = LoadModel(filepath);
	ConvertMeshesOnNode(scene->mRootNode, scene);
}

const aiScene* Model::LoadModel(const string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw "Assimp error: " + (string)(importer.GetErrorString());

	this->filepath = filepath.substr(0, filepath.find_last_of('/'));
	return scene;
}

void Model::ConvertMeshesOnNode(const aiNode* node, const aiScene* scene)
{
	for (Uint32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshComponents.push_back(ConvertMeshToComponent(mesh, scene));
	}

	for (Uint32 i = 0; i < node->mNumChildren; i++)
		ConvertMeshesOnNode(node->mChildren[i], scene);
}

MeshComponent* Model::ConvertMeshToComponent(const aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices = ConvertVertices(mesh);
	vector<Uint32> indices = ConvertIndices(mesh);

	return new MeshComponent(vertices, indices);
}

vector<Vertex> Model::ConvertVertices(const aiMesh* mesh)
{
	vector<Vertex> vertices(mesh->mNumVertices);
	for (Uint32 i = 0; i < vertices.size(); i++)
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

Model::~Model()
{
	for (auto& meshComponent : meshComponents)
		delete meshComponent;
}
