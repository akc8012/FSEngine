#pragma once
#include <SDL.h>

class Timer
{
private:
	enum State { Stopped, Running, Paused };
	State state = Stopped;

	unsigned int ticks = 0;
	unsigned int pausedTicks = 0;

	void CalculatePausedTicks();
	void ResetStartingTicks();

public:
	static float GetSeconds();

	void Start();
	void Stop();

	void Pause();
	void UnPause();
	void TogglePause();

	unsigned int GetTimerTicks() const;
	float GetTimerSeconds() const;
	bool IsRunning() const;
	bool IsPaused() const;
};
