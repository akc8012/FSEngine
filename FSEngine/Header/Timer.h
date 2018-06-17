#pragma once
#include <SDL.h>

class Timer
{
private:
	static float lastTime;

	enum State { Stopped, Running, Paused };
	State state = Stopped;

	unsigned int ticks = 0;
	unsigned int pausedTicks = 0;

	void calculatePausedTicks();
	void resetStartingTicks();

public:
	static float getSeconds();
	static float getDeltaTime();
	static void update();

	void start();
	void stop();

	void pause();
	void unpause();
	void togglePause();

	unsigned int getTimerTicks() const;
	bool isRunning() const;
	bool isPaused() const;
};
