#include "../Header/Timer.h"
#include <stdio.h>

#pragma region Static Methods
float Timer::lastTime = 0.0f;
unsigned int Timer::countedFrames = 0;
Timer* Timer::frameRateTimer = NULL;

void Timer::Init()
{
	frameRateTimer = new Timer();
	frameRateTimer->Start();
}

float Timer::GetDeltaTime()
{
	float currentTime = GetSeconds();
	return currentTime - lastTime;
}

float Timer::GetFramesPerSecond()
{
	return (float)countedFrames / (frameRateTimer->GetTimerSeconds());
}

void Timer::Update()
{
	lastTime = GetSeconds();
	countedFrames++;
}

float Timer::GetSeconds()
{
	return (float)SDL_GetTicks() / 1000.0f;
}

void Timer::Close()
{
	delete frameRateTimer;
}
#pragma endregion

#pragma region Member Methods
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

unsigned int Timer::GetTimerTicks() const
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
#pragma endregion
