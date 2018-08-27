#include "../Header/GameTimer.h"

GameTimer::GameTimer()
{
	Start();
}

void GameTimer::UpdateDeltaTime()
{
	float currentFrameTime = GetSeconds();
	deltaTime = currentFrameTime - lastFrameTime;

	lastFrameTime = currentFrameTime;
}

float GameTimer::GetDeltaTime() const
{
	return deltaTime;
}
