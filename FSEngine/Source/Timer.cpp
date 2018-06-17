#include "../Header/Timer.h"

#pragma region Static Methods
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

bool Timer::isRunning() const
{
	return state == Running;
}

bool Timer::isPaused() const
{
	return state == Paused;
}
#pragma endregion
