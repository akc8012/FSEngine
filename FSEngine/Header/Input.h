#pragma once
#include <SDL.h>

#include <glm\glm.hpp>
using glm::tvec2;

#include <algorithm>

class Input
{
private:
	int numberOfKeys;

	const Uint8* keyboardState = nullptr;
	Uint8* lastKeyboardState = nullptr;
	tvec2<int> lastCursorPosition = tvec2<int>(0, 0);

	int mouseWheelScroll = 0;
	bool mouseButtonState[3] = { false, false, false };
	bool lastMouseButtonState[3] = { false, false, false };

	SDL_GameController* gameController;

	void UpdateLastKeyboardState();
	void UpdateLastCursorPosition();
	void UpdateLastMouseButtonState();
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

	void SetMouseButtonPress(int button);
	void SetMouseButtonRelease(int button);

	tvec2<int> GetCursorDelta() const;
	tvec2<int> GetCursorPosition() const;
	tvec2<int> GetLastCursorPosition() const;

	bool IsButtonPressed(const SDL_Scancode& button) const;
	bool IsButtonPressed(int button) const;

	bool IsButtonReleased(const SDL_Scancode& button) const;
	bool IsButtonReleased(int button) const;

	bool IsButtonHeld(const SDL_Scancode& button) const;
	bool IsButtonHeld(int button) const;
};
