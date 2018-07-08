#pragma once
#include "Vertex.h"
#include "MeshComponent.h"
#include "TextureComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
using std::string;
using std::vector;

class Model
{
private:
	vector<MeshComponent*> meshComponents;
	string filepath;

	const aiScene* LoadModel(const string& filepath);

	void ConvertMeshesOnNode(const aiNode* node, const aiScene* scene);
	MeshComponent* ConvertMeshToComponent(const aiMesh* mesh);

	vector<Vertex> ConvertVertices(const aiMesh* mesh);
	vector<Uint32> ConvertIndices(const aiMesh* mesh);

public:
	Model(const string& filepath);
	~Model();
};
