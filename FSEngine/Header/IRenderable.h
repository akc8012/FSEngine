#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Texture.h"

class IRenderable
{
public:
	virtual ~IRenderable()
	{

	}

	virtual ComponentCollection<Mesh>* GetMeshCollection() const = 0;
	virtual ComponentCollection<Texture>* GetTextureCollection() const = 0;
};
