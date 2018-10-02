#pragma once
#include "ComponentContainer.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

struct Components
{
	Components()
	{
		meshComponents = make_unique<ComponentContainer<Mesh>>();
		shadingComponents = make_unique<ComponentContainer<Shading>>();
		transformComponents = make_unique<ComponentContainer<Transform>>();
	}

	unique_ptr<ComponentContainer<Mesh>> meshComponents;
	unique_ptr<ComponentContainer<Shading>> shadingComponents;
	unique_ptr<ComponentContainer<Transform>> transformComponents;
};
