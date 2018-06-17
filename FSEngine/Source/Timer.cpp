#include "../Header/Timer.h"
#include <stdio.h>

#pragma region Static Methods
float Timer::lastTime = 0.0f;
unsigned int Timer::countedFrames = 0;
float Timer::initOffset = 0.0f;

void Timer::init()
{
	initOffset = getSeconds();
}

void Timer::update()
{
	lastTime = getSeconds();
	countedFrames++;
}

float Timer::getDeltaTime()
{
	float currentTime = getSeconds();
	return currentTime - lastTime;
}

float Timer::getFramesPerSecond()
{
	return (float)(countedFrames - 1) / (getSeconds() - initOffset);
}

float Timer::getSeconds()
{
	return (float)SDL_GetTicks() / 1000.0f;
}
#pragma endregion

#pragma region Member Methods
void Timer::start()
{
	state = Running;

	ticks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stop()
{
	state = Stopped;

	ticks = 0;
	pausedTicks = 0;
}

void Timer::pause()
{
	if (state == Running)
	{
		state = Paused;

		calculatePausedTicks();
		ticks = 0;
	}
}

void Timer::calculatePausedTicks()
{
	pausedTicks = SDL_GetTicks() - ticks;
}

void Timer::unpause()
{
	if (state == Paused)
	{
		state = Running;
		resetStartingTicks();
	}
}

void Timer::resetStartingTicks()
{
	ticks = SDL_GetTicks() - pausedTicks;
	pausedTicks = 0;
}

void Timer::togglePause()
{
	if (state == Paused)
		unpause();
	else if (state == Running)
		pause();
}

unsigned int Timer::getTimerTicks() const
{
	switch (state)
	{
		case Running:
			return SDL_GetTicks() - ticks;

		case Paused:
			return pausedTicks;

		case Stopped:
		default:
			return 0;
	}
}

float Timer::getTimerSeconds() const
{
	return (float)getTimerTicks() / 1000.0f;
}

bool Timer::isRunning() const
{
	return state == Running;
}

bool Timer::isPaused() const
{
	return state == Paused;
}
#pragma endregion
