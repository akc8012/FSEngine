#pragma once
#include "ComponentContainer.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

struct Components
{
	Components()
	{
		mesh = make_unique<ComponentContainer<Mesh>>();
		shading = make_unique<ComponentContainer<Shading>>();
		transform = make_unique<ComponentContainer<Transform>>();
	}

	unique_ptr<ComponentContainer<Mesh>> mesh;
	unique_ptr<ComponentContainer<Shading>> shading;
	unique_ptr<ComponentContainer<Transform>> transform;
};
