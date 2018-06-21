#pragma once
#include <SDL.h>

class Timer
{
private:
	enum State { Stopped, Running, Paused };
	State state = Stopped;

	Uint32 ticks = 0;
	Uint32 pausedTicks = 0;

	void CalculatePausedTicks();
	void ResetStartingTicks();

public:
	static float GetSeconds();

	void Start();
	void Stop();

	void Pause();
	void UnPause();
	void TogglePause();

	Uint32 GetTimerTicks() const;
	float GetTimerSeconds() const;
	bool IsRunning() const;
	bool IsPaused() const;
};
