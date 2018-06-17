#pragma once

class LTimer
{
private:
	enum State { Stopped, Running, Paused };
	State state = Stopped;

	unsigned int ticks = 0;
	unsigned int pausedTicks = 0;

	void calculatePausedTicks();
	void resetStartingTicks();

public:
	void start();
	void stop();

	void pause();
	void unpause();
	void togglePause();

	unsigned int getTicks() const;

	bool isRunning() const;
	bool isPaused() const;
};
