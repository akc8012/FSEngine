#pragma once
#include "FileSystem.h"
#include "Input.h"

struct Systems
{
	Systems();
	~Systems();

	FileSystem* fileSystem;
	Input* input;
};
