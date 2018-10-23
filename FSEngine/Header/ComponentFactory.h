#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"

#include <string>
#include <memory>
using std::string;
using std::shared_ptr;
using std::make_shared;

class ComponentFactory
{
public:
	static shared_ptr<Component> MakeComponent(const string& type);

};
