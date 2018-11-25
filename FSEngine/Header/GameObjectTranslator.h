#pragma once
#include "IGameObject.h"
#include "Camera.h"

class GameObjectTranslator
{
private:
	const int TranslateButton = SDL_BUTTON_LEFT;
	const SDL_Scancode VerticalButton = SDL_SCANCODE_LSHIFT;

	Input* input = nullptr;
	Camera* camera = nullptr;

	IGameObject* gameObject;
	vec3 cursorOffset;
	vec3 originalPosition;

	vec3 CalculateTargetPosition(const vec3& objectPosition) const;

	plane GetFloorPlane(const vec3& objectPosition) const;
	plane GetVerticalPlane(const vec3& objectPosition) const;

	vec3 CalculatePositionAlongPlane(const plane& plane) const;
	vec3 CalculateVerticalPositionAlongPlane(const plane& plane) const;
	bool ShouldResetCursorOffset() const;

public:
	GameObjectTranslator(Input* input, Camera* camera);

	void SetGameObject(IGameObject* gameObject);
	void TranslateGameObject();
	json GetHistoryAction() const;
	void DoUndoAction(const json& action, IGameObject* gameObject);

	bool ShouldStartTranslate() const;
	bool ShouldTranslate() const;
	bool ShouldEndTranslate() const;
};
