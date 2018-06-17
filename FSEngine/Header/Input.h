#pragma once
#include <SDL.h>

class Input
{
private:
	static float getAnalogAxis(SDL_GameControllerAxis axis);
	static float getDigitalAxis(SDL_Scancode positiveInput, SDL_Scancode negativeInput);

public:
	static float getHorizontalAxis();
	static float getVerticalAxis();
};
