#pragma once
#include "Timer.h"

class GameTimer : public Timer
{
private:
	int frames = 0;
	float lastFrameTime = 0;
	float deltaTime = 0;

	void UpdateDeltaTime();

public:
	GameTimer();

	void Update();
	float GetDeltaTime() const;
	int GetFrames() const;
};
