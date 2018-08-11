#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using Assimp::Importer;

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::unique_ptr;

class Model : public GameObject
{
private:
	string directory = "";

	unique_ptr<Importer> LoadModelImporter(const char* filepath);

	void ConvertMeshesOnNode(const aiNode* node, const aiScene* scene);

	MeshComponent* ConvertMeshToComponent(const aiMesh* mesh);
	void ConvertMaterialToTextures(MeshComponent* meshComponent, const aiMaterial* material);

	vector<Vertex> ConvertVertices(const aiMesh* mesh);
	vector<Uint32> ConvertIndices(const aiMesh* mesh);

	string* GetLoadedTextureName(const string& texturePath) const;

public:
	Model(const string& filepath);

	void Update(float deltaTime);
};
