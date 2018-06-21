#pragma once
#include <SDL.h>

#include <algorithm>
using namespace std;

class Input
{
private:
	static float GetAnalogAxis(SDL_GameControllerAxis axis);
	static float GetDigitalAxis(SDL_Scancode positiveInput, SDL_Scancode negativeInput);

public:
	static float GetHorizontalAxis();
	static float GetVerticalAxis();
};
