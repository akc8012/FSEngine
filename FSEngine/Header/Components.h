#pragma once
#include "ComponentContainer.h"
#include "Mesh.h"
#include "Shading.h"
#include "Transform.h"

using std::make_shared;

struct Components
{
	Components()
	{
		meshComponents = make_shared<ComponentContainer<Mesh>>();
		shadingComponents = make_shared<ComponentContainer<Shading>>();
		transformComponents = make_shared<ComponentContainer<Transform>>();
	}

	shared_ptr<ComponentContainer<Mesh>> meshComponents;
	shared_ptr<ComponentContainer<Shading>> shadingComponents;
	shared_ptr<ComponentContainer<Transform>> transformComponents;
};
