#include "../Header/Input.h"
#include <algorithm>
using namespace std;

float Input::getHorizontalAxis()
{
	float axis = getDigitalAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT) + getDigitalAxis(SDL_SCANCODE_D, SDL_SCANCODE_A);
	return clamp(axis, -1.0f, 1.0f);;
}

float Input::getVerticalAxis()
{
	float axis = getDigitalAxis(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN) + getDigitalAxis(SDL_SCANCODE_W, SDL_SCANCODE_S);
	return clamp(axis, -1.0f, 1.0f);
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
