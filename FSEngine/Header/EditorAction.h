#pragma once
#include "FSMath.h"

#include <string>
using std::string;

struct Action
{

};

struct MoveAction : Action
{
	vec3 moveDelta;
};

struct EditorAction
{
	string affectedGameObject;
	Action action;
};
