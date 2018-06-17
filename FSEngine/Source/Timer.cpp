#include "../Header/Timer.h"

float Timer::lastTime = 0.0f;

float Timer::getSeconds()
{
	return (float)SDL_GetTicks() / 1000.0f;
}

float Timer::getDeltaTime()
{
	float currentTime = getSeconds();
	return currentTime - lastTime;
}

void Timer::update()
{
	lastTime = getSeconds();
}
