#include "../Header/GameObjectTranslator.h"

GameObjectTranslator::GameObjectTranslator(Input* input, Camera* camera)
 : input(input), camera(camera)
{

}

void GameObjectTranslator::SetGameObject(IGameObject* gameObject)
{
	this->gameObject = gameObject;

	if (gameObject != nullptr)
		originalPosition = gameObject->GetComponent<Transform>()->GetPosition();
}

void GameObjectTranslator::TranslateGameObject()
{
	auto transform = gameObject->GetComponent<Transform>();
	vec3 targetPosition = CalculateTargetPosition(transform->GetPosition());

	if (ShouldResetCursorOffset())
		cursorOffset = targetPosition - transform->GetPosition();

	transform->SetPosition(targetPosition - cursorOffset);
}

vec3 GameObjectTranslator::CalculateTargetPosition(const vec3& objectPosition) const
{
	if (!input->IsButtonHeld(VerticalButton))
		return CalculatePositionAlongPlane(GetFloorPlane(objectPosition));
	else
		return CalculateVerticalPositionAlongPlane(GetVerticalPlane(objectPosition));
}

plane GameObjectTranslator::GetFloorPlane(const vec3& objectPosition) const
{
	return plane(vec3(0, objectPosition.y, 0), FSMath::Up);
}

plane GameObjectTranslator::GetVerticalPlane(const vec3& objectPosition) const
{
	auto cameraDirection = vec3(camera->GetForward().x, 0, -camera->GetForward().z);
	return plane(objectPosition, cameraDirection);
}

vec3 GameObjectTranslator::CalculatePositionAlongPlane(const plane& plane) const
{
	auto cursorRay = camera->GetCursorRay();

	auto distance = FSMath::RayIntersectPlaneDistance(plane, cursorRay);
	return vec3(cursorRay.origin + (cursorRay.direction * distance));
}

vec3 GameObjectTranslator::CalculateVerticalPositionAlongPlane(const plane& plane) const
{
	auto position = CalculatePositionAlongPlane(plane);
	return vec3(0, position.y, 0);
}

bool GameObjectTranslator::ShouldResetCursorOffset() const
{
	return  input->IsButtonPressed(TranslateButton) ||
			input->IsButtonPressed(VerticalButton) ||
			input->IsButtonReleased(VerticalButton);
}

json GameObjectTranslator::GetHistoryAction() const
{
	json action;
	action["ActionType"] = "Translate";
	action["GameObject"] = gameObject->GetName();

	vec3 moveDelta = gameObject->GetComponent<Transform>()->GetPosition() - originalPosition;
	action["MoveDelta"] = { moveDelta.x, moveDelta.y, moveDelta.z };

	return action;
}

void GameObjectTranslator::DoUndoAction(const json& action, IGameObject* gameObject)
{
	vec3 moveDelta = vec3(action["MoveDelta"][0], action["MoveDelta"][1], action["MoveDelta"][2]);
	gameObject->GetComponent<Transform>()->Translate(-moveDelta);
}

bool GameObjectTranslator::ShouldStartTranslate() const
{
	return input->IsButtonPressed(TranslateButton);
}

bool GameObjectTranslator::ShouldTranslate() const
{
	return input->IsButtonHeld(TranslateButton);
}

bool GameObjectTranslator::ShouldEndTranslate() const
{
	return input->IsButtonReleased(TranslateButton);
}
