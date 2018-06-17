#include "../Header/LTimer.h"
#include <SDL.h>

void LTimer::start()
{
	state = Running;

	ticks = SDL_GetTicks();
	pausedTicks = 0;
}

void LTimer::stop()
{
	state = Stopped;

	ticks = 0;
	pausedTicks = 0;
}

void LTimer::pause()
{
	if (state == Running)
	{
		state = Paused;

		calculatePausedTicks();
		ticks = 0;
	}
}

void LTimer::calculatePausedTicks()
{
	pausedTicks = SDL_GetTicks() - ticks;
}

void LTimer::unpause()
{
	if (state == Paused)
	{
		state = Running;
		resetStartingTicks();
	}
}

void LTimer::resetStartingTicks()
{
	ticks = SDL_GetTicks() - pausedTicks;
	pausedTicks = 0;
}

void LTimer::togglePause()
{
	if (state == Paused)
		unpause();
	else if (state == Running)
		pause();
}

unsigned int LTimer::getTicks() const
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

bool LTimer::isRunning() const
{
	return state == Running;
}

bool LTimer::isPaused() const
{
	return state == Paused;
}
