#include "../Header/Input.h"

Input::Input()
{
	const int JoystickIndex = 0;
	gameController = SDL_GameControllerOpen(JoystickIndex);
}

float Input::GetHorizontalAxis()
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTX) + GetDigitalAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT) + GetDigitalAxis(SDL_SCANCODE_D, SDL_SCANCODE_A);
	return clamp(axis, -1.0f, 1.0f);
}

float Input::GetVerticalAxis()
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTY) + GetDigitalAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP) + GetDigitalAxis(SDL_SCANCODE_S, SDL_SCANCODE_W);
	return clamp(axis, -1.0f, 1.0f);
}

float Input::GetAnalogAxis(const SDL_GameControllerAxis& axis)
{
	Sint16 input = SDL_GameControllerGetAxis(gameController, axis);
	return ClampAnalogInput(input);
}

float Input::ClampAnalogInput(Sint16 input)
{
	const int MaxInt = 32767;
	float analogInput = clamp((float)input / MaxInt, -1.0f, 1.0f);

	const float DeadZone = 0.1f;
	return abs(analogInput) > DeadZone ? analogInput : 0.0f;
}

float Input::GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput)
{
	float axis = 0;
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[positiveInput])
		axis++;
	if (keyboardState[negativeInput])
		axis--;

	return axis;
}

Input::~Input()
{
	SDL_GameControllerClose(gameController);
}
