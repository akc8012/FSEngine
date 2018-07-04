#pragma once
#include <SDL.h>

#include <algorithm>

class Input
{
private:
	static float GetAnalogAxis(const SDL_GameControllerAxis& axis);
	static float GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput);

public:
	static float GetHorizontalAxis();
	static float GetVerticalAxis();
};
