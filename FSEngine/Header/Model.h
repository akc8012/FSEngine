#pragma once
#include "Component.h"
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Texture.h"
#include "FSDebug.h"
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
using std::shared_ptr;
using std::make_shared;

class Model
{
private:
	string filepath;
	unique_ptr<ComponentCollection<Mesh>> meshComponents;
	unique_ptr<ComponentCollection<Texture>> textureComponents;

	unique_ptr<Importer> LoadModelImporter(const string& filepath);

	void ConvertMeshesOnNode(const aiNode* node, const aiScene* scene);

	shared_ptr<Mesh> ConvertMeshToComponent(const aiMesh* mesh);
	vector<Vertex> ConvertVertices(const aiMesh* mesh);
	vector<Uint32> ConvertIndices(const aiMesh* mesh);

	void ConvertMaterialToTextures(Mesh* meshComponent, const aiMaterial* material);
	void AddTextureComponent(Mesh* meshComponent, const string& textureName);

	string* TryGetLoadedTextureName(const string& textureName) const;

	string GetDirectory() const;

public:
	Model(const string& filepath);
};
