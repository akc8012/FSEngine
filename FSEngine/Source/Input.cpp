#include "../Header/Input.h"

float Input::GetHorizontalAxis()
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTX) + GetDigitalAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT) + GetDigitalAxis(SDL_SCANCODE_D, SDL_SCANCODE_A);
	return std::clamp(axis, -1.0f, 1.0f);
}

float Input::GetVerticalAxis()
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTY) + GetDigitalAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP) + GetDigitalAxis(SDL_SCANCODE_S, SDL_SCANCODE_W);
	return std::clamp(axis, -1.0f, 1.0f);
}

float Input::GetAnalogAxis(const SDL_GameControllerAxis& axis)
{
	const int JoystickIndex = 0;
	SDL_GameController* gameController = SDL_GameControllerOpen(JoystickIndex);
	Sint16 analogInputInt = SDL_GameControllerGetAxis(gameController, axis);
	SDL_GameControllerClose(gameController);

	const int MaxInt = 32767;
	float analogInput = std::clamp((float)analogInputInt / MaxInt, -1.0f, 1.0f);

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
