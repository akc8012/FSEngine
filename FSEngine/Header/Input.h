#pragma once
#include <SDL.h>

#include <algorithm>

class Input
{
private:
	int numberOfKeys;
	const Uint8* keyboardState = nullptr;
	Uint8* lastKeyboardState = nullptr;

	SDL_GameController* gameController;

	float GetAnalogAxis(const SDL_GameControllerAxis& axis) const;
	float ClampAnalogInput(Sint16 input) const;

	float Clamp(float value, float low, float high) const;

public:
	Input();
	~Input();

	void UpdateLastKeyboardState();

	float GetHorizontalAxis() const;
	float GetVerticalAxis() const;

	float GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput) const;

	bool IsButtonPressed(const SDL_Scancode& button) const;
	bool IsButtonReleased(const SDL_Scancode& button) const;
	bool IsButtonHeld(const SDL_Scancode& button) const;
};
