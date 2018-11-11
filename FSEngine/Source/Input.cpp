#include "../Header/Input.h"

Input::Input()
{
	const int JoystickIndex = 0;
	gameController = SDL_GameControllerOpen(JoystickIndex);

	keyboardState = SDL_GetKeyboardState(&numberOfKeys);
	UpdateLastKeyboardState();
}

void Input::Update()
{
	UpdateLastKeyboardState();

	UpdateLastCursorPosition();

	UpdateLastMouseButtonState();

	ResetMouseWheelScroll();
}

void Input::UpdateLastKeyboardState()
{
	delete lastKeyboardState;
	lastKeyboardState = new Uint8[numberOfKeys];

	std::copy(keyboardState, keyboardState + numberOfKeys, lastKeyboardState);
}

void Input::UpdateLastCursorPosition()
{
	lastCursorPosition = GetCursorPosition();
}

void Input::UpdateLastMouseButtonState()
{
	for (int i = 0; i < 3; i++)
		lastMouseButtonState[i] = mouseButtonState[i];
}

void Input::ResetMouseWheelScroll()
{
	mouseWheelScroll = 0;
}

float Input::GetHorizontalAxis() const
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTX) + GetDigitalAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT) + GetDigitalAxis(SDL_SCANCODE_D, SDL_SCANCODE_A);
	return Clamp(axis, -1.0f, 1.0f);
}

float Input::GetVerticalAxis() const
{
	float axis = GetAnalogAxis(SDL_CONTROLLER_AXIS_LEFTY) + GetDigitalAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP) + GetDigitalAxis(SDL_SCANCODE_S, SDL_SCANCODE_W);
	return Clamp(axis, -1.0f, 1.0f);
}

float Input::GetAnalogAxis(const SDL_GameControllerAxis& axis) const
{
	Sint16 input = SDL_GameControllerGetAxis(gameController, axis);
	return ClampAnalogInput(input);
}

float Input::ClampAnalogInput(Sint16 input) const
{
	const int MaxInt = 32767;
	float analogInput = Clamp((float)input / MaxInt, -1.0f, 1.0f);

	const float DeadZone = 0.1f;
	return abs(analogInput) > DeadZone ? analogInput : 0.0f;
}

float Input::Clamp(float value, float low, float high) const
{
	return std::max(low, std::min(value, high));
}

float Input::GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput) const
{
	float axis = 0;
	if (IsButtonHeld(positiveInput))
		axis++;
	if (IsButtonHeld(negativeInput))
		axis--;

	return axis;
}

void Input::SetMouseWheelScroll(int mouseWheelScroll)
{
	this->mouseWheelScroll = mouseWheelScroll;
}

int Input::GetMouseWheelScroll() const
{
	return mouseWheelScroll;
}

void Input::SetMouseButtonPress(int button)
{
	const int SdlButtonEnumOffset = 1;
	mouseButtonState[button - SdlButtonEnumOffset] = true;
}

void Input::SetMouseButtonRelease(int button)
{
	const int SdlButtonEnumOffset = 1;
	mouseButtonState[button - SdlButtonEnumOffset] = false;
}

tvec2<int> Input::GetCursorDelta() const
{
	return GetCursorPosition() - lastCursorPosition;
}

tvec2<int> Input::GetCursorPosition() const
{
	tvec2<int> cursorPosition = tvec2<int>(0, 0);
	SDL_GetMouseState(&cursorPosition.x, &cursorPosition.y);

	return cursorPosition;
}

tvec2<int> Input::GetLastCursorPosition() const
{
	return lastCursorPosition;
}

bool Input::IsButtonPressed(const SDL_Scancode& button) const
{
	return !lastKeyboardState[button] && IsButtonHeld(button);
}

bool Input::IsButtonReleased(const SDL_Scancode& button) const
{
	return lastKeyboardState[button] && !IsButtonHeld(button);
}

bool Input::IsButtonHeld(const SDL_Scancode& button) const
{
	return keyboardState[button];
}

bool Input::IsButtonPressed(int button) const
{
	const int SdlButtonEnumOffset = 1;
	return !lastMouseButtonState[button - SdlButtonEnumOffset] && mouseButtonState[button - SdlButtonEnumOffset];
}

bool Input::IsButtonReleased(int button) const
{
	const int SdlButtonEnumOffset = 1;
	return lastMouseButtonState[button - SdlButtonEnumOffset] && !mouseButtonState[button - SdlButtonEnumOffset];
}

bool Input::IsButtonHeld(int button) const
{
	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
}

Input::~Input()
{
	delete lastKeyboardState;
	SDL_GameControllerClose(gameController);
}
