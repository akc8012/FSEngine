#include "../Header/Timer.h"

float Timer::GetSeconds()
{
	return MsToSeconds(SDL_GetTicks());
}

float Timer::MsToSeconds(Uint32 ms)
{
	return (float)ms / 1000.0f;
}

void Timer::Start()
{
	state = Running;

	ticks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::Stop()
{
	state = Stopped;

	ticks = 0;
	pausedTicks = 0;
}

void Timer::Pause()
{
	if (state == Running)
	{
		state = Paused;

		CalculatePausedTicks();
		ticks = 0;
	}
}

void Timer::CalculatePausedTicks()
{
	pausedTicks = SDL_GetTicks() - ticks;
}

void Timer::UnPause()
{
	if (state == Paused)
	{
		state = Running;
		ResetStartingTicks();
	}
}

void Timer::ResetStartingTicks()
{
	ticks = SDL_GetTicks() - pausedTicks;
	pausedTicks = 0;
}

void Timer::TogglePause()
{
	if (state == Paused)
		UnPause();
	else if (state == Running)
		Pause();
}

Uint32 Timer::GetTimerTicks() const
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

float Timer::GetTimerSeconds() const
{
	return (float)GetTimerTicks() / 1000.0f;
}

bool Timer::IsRunning() const
{
	return state == Running;
}

bool Timer::IsPaused() const
{
	return state == Paused;
}
