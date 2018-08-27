#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "ShaderProgram.h"
#include "GameTimer.h"

struct Systems
{
	FileSystem* fileSystem = nullptr;
	Input* input = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	GameTimer* gameTimer = nullptr;
};
