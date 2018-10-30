#pragma once
#include <string>
#include <algorithm>
using std::string;

namespace Types
{
	enum ComponentType { Component, Mesh, Color, Transform, Texture, Model, ComponentsLength };
	static const char*  ComponentTypeString[] = { "Component", "Mesh", "Color", "Transform", "Texture", "Model" };

	ComponentType StringToComponentType(const string& componentString);
}
