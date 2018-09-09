#pragma once
#include <SDL.h>

#include <glm\glm.hpp>
using glm::tvec2;

#include <algorithm>

class Input
{
private:
	int numberOfKeys;
	int mouseWheelScroll = 0;
	const Uint8* keyboardState = nullptr;
	Uint8* lastKeyboardState = nullptr;
	tvec2<int> lastCursorPosition = tvec2<int>(0, 0);

	SDL_GameController* gameController;

	void UpdateLastKeyboardState();
	void UpdateLastCursorPosition();
	void ResetMouseWheelScroll();

	float GetAnalogAxis(const SDL_GameControllerAxis& axis) const;
	float ClampAnalogInput(Sint16 input) const;

	float Clamp(float value, float low, float high) const;

public:
	Input();
	~Input();

	void Update();

	float GetHorizontalAxis() const;
	float GetVerticalAxis() const;

	float GetDigitalAxis(const SDL_Scancode& positiveInput, const SDL_Scancode& negativeInput) const;

	void SetMouseWheelScroll(int mouseWheelScroll);
	int GetMouseWheelScroll() const;

	tvec2<int> GetCursorDelta() const;
	tvec2<int> GetCursorPosition() const;

	bool IsButtonPressed(const SDL_Scancode& button) const;
	bool IsButtonReleased(const SDL_Scancode& button) const;
	bool IsButtonHeld(const SDL_Scancode& button) const;
	bool IsButtonHeld(int button) const;
};
