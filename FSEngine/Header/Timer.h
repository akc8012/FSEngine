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

	void calculatePausedTicks();
	void resetStartingTicks();

public:
	static void init();
	static void update();

	static float getDeltaTime();
	static float getFramesPerSecond();
	static float getSeconds();

	void start();
	void stop();

	void pause();
	void unpause();
	void togglePause();

	unsigned int getTimerTicks() const;
	float getTimerSeconds() const;
	bool isRunning() const;
	bool isPaused() const;
};
