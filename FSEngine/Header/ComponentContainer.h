#pragma once
#include "ComponentCollection.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

struct ComponentContainer
{
	ComponentContainer()
	{
		mesh = make_unique<ComponentCollection<Mesh>>();
		shading = make_unique<ComponentCollection<Shading>>();
		transform = make_unique<ComponentCollection<Transform>>();
	}

	unique_ptr<ComponentCollection<Mesh>> mesh;
	unique_ptr<ComponentCollection<Shading>> shading;
	unique_ptr<ComponentCollection<Transform>> transform;
};
