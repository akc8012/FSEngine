#pragma once
#include <SDL.h>

class Timer
{
private:
	static float lastTime;

public:
	static float getSeconds();
	static float getDeltaTime();

	static void update();
};
