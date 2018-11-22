#pragma once
#include "IUpdatable.h"
#include "Timer.h"

class GameTimer : public Timer, public IUpdatable
{
private:
	int frames = 0;
	float lastFrameTime = 0;
	float deltaTime = 0;

	void UpdateDeltaTime();

public:
	GameTimer();

	void Update() override;
	float GetDeltaTime() const;
	int GetFrames() const;
};
