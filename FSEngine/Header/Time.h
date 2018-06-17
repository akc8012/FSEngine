#pragma once
#include <SDL.h>

class Time
{
private:
	static float lastTime;

public:
	static float getSeconds();
	static float getDeltaTime();

	static void update();
};
