#pragma once
#include <SDL.h>

#include <algorithm>

class Input
{
private:
	SDL_GameController * gameController;

	float GetAnalogAxis(const SDL_GameControllerAxis& axis);
	float GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput);
	float ClampAnalogInput(Sint16 input);

	float Clamp(float value, float low, float high) const;

public:
	Input();
	~Input();

	float GetHorizontalAxis();
	float GetVerticalAxis();
};
