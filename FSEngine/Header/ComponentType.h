#pragma once
#include <string>
#include <algorithm>
using std::string;

namespace Types
{
	enum ComponentType { Component, Mesh, Color, Transform, Texture, FontTexture, Model, ComponentsLength };
	static const char*  ComponentTypeString[] = { "Component", "Mesh", "Color", "Transform", "Texture", "FontTexture", "Model" };

	ComponentType StringToComponentType(const string& componentString);
}
