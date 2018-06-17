#include "../Header/Input.h"
#include <algorithm>
using namespace std;

float Input::getHorizontalAxis()
{
	float axis = getAnalogAxis(SDL_CONTROLLER_AXIS_LEFTX) + getDigitalAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT) + getDigitalAxis(SDL_SCANCODE_D, SDL_SCANCODE_A);
	return clamp(axis, -1.0f, 1.0f);
}

float Input::getVerticalAxis()
{
	float axis = getAnalogAxis(SDL_CONTROLLER_AXIS_LEFTY) + getDigitalAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP) + getDigitalAxis(SDL_SCANCODE_S, SDL_SCANCODE_W);
	return clamp(axis, -1.0f, 1.0f);
}

float Input::getAnalogAxis(SDL_GameControllerAxis axis)
{
	const int JoystickIndex = 0;
	SDL_GameController* gameController = SDL_GameControllerOpen(JoystickIndex);
	Sint16 analogInputInt = SDL_GameControllerGetAxis(gameController, axis);
	SDL_GameControllerClose(gameController);

	const int MaxInt = 32767;
	float analogInput = clamp((float)analogInputInt / MaxInt, -1.0f, 1.0f);

	const float DeadZone = 0.1f;
	return abs(analogInput) > DeadZone ? analogInput : 0.0f;
}

float Input::getDigitalAxis(SDL_Scancode positiveInput, SDL_Scancode negativeInput)
{
	float axis = 0;
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[positiveInput])
		axis++;
	if (keyboardState[negativeInput])
		axis--;

	return axis;
}
