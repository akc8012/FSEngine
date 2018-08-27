#pragma once
#include "Timer.h"

class GameTimer : public Timer
{
private:
	float lastFrameTime = 0;
	float deltaTime = 0;

public:
	GameTimer();

	void UpdateDeltaTime();
	float GetDeltaTime() const;
};
