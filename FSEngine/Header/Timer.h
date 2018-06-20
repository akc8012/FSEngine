#pragma once
#include <SDL.h>

class Timer
{
private:
	static float lastTime;
	static unsigned int countedFrames;
	static Timer* frameRateTimer;

	enum State { Stopped, Running, Paused };
	State state = Stopped;

	unsigned int ticks = 0;
	unsigned int pausedTicks = 0;

	void CalculatePausedTicks();
	void ResetStartingTicks();

public:
	static void Init();
	static void Update();
	static void Close();

	static float GetDeltaTime();
	static float GetFramesPerSecond();
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
