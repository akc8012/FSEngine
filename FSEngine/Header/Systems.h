#pragma once
#include "FileSystem.h"
#include "Input.h"
#include "ShaderProgram.h"
#include "GameTimer.h"
#include "Random.h"
#include "EventSystem.h"

#include <memory>
using std::unique_ptr;
using std::make_unique;

struct Systems
{
	unique_ptr<FileSystem> fileSystem;
	unique_ptr<Input> input;
	unique_ptr<ShaderProgram> shaderProgram;
	unique_ptr<GameTimer> gameTimer;
	unique_ptr<Random> random;
	unique_ptr<EventSystem> eventSystem;
};
