#include "../Header/Time.h"

float Time::lastTime = 0.0f;

float Time::getSeconds()
{
	return (float)SDL_GetTicks() / 1000.0f;
}

float Time::getDeltaTime()
{
	float currentTime = getSeconds();
	return currentTime - lastTime;
}

void Time::update()
{
	lastTime = getSeconds();
}
