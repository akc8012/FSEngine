#pragma once
#include <string>
#include <algorithm>
using std::string;

namespace Types
{
	enum ComponentType                          {  Component ,  Mesh ,  Shading ,  Color ,  Texture ,  FontTexture ,  Transform ,  Transform2D ,  Model ,  ComponentsLength };
	static const char*  ComponentTypeString[] = { "Component", "Mesh", "Shading", "Color", "Texture", "FontTexture", "Transform", "Transform2D", "Model" };

	ComponentType StringToComponentType(const string& componentString);
}
