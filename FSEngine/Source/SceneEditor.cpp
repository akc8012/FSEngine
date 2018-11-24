#include "../Header/SceneEditor.h"

SceneEditor::SceneEditor(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	clickLabelManager = make_unique<ClickLabelManager>(scene, systems);
	InitializeEditor();
}

void SceneEditor::InitializeEditor()
{
	UpdateEditorMode();

	clickLabelManager->CreateClickLabels();
	camera = scene->GetGameObjectContainer()->GetGameObjectAs<Camera>("Camera");
}

void SceneEditor::Update()
{
	UpdateEditorMode();

	if (editorMode)
	{
		clickLabelManager->Update();

		if (systems->input->IsButtonHeld(SDL_BUTTON_LEFT))
			TranslateActiveGameObject(clickLabelManager->GetActiveGameObject());
	}
}

void SceneEditor::UpdateEditorMode()
{
	bool editorModeSetting = systems->fileSystem->GetSettingsValue<bool>("EditorMode");
	if (editorMode && !editorModeSetting)
		systems->eventSystem->SendEvent("EditorModeDisabled", nullptr, false);
	else if (!editorMode && editorModeSetting)
		systems->eventSystem->SendEvent("EditorModeEnabled", nullptr, false);

	editorMode = editorModeSetting;
}

void SceneEditor::TranslateActiveGameObject(IGameObject* activeGameObject)
{
	if (activeGameObject == nullptr)
		return;

	auto transform = activeGameObject->GetComponent<Transform>();
	
	vec3 targetPosition;
	if (!systems->input->IsButtonHeld(SDL_SCANCODE_LSHIFT))
		targetPosition = CalculatePositionAlongPlane(GetFloorPlane(transform->GetPosition()));
	else
		targetPosition = CalculateVerticalPositionAlongPlane(GetVerticalPlane(transform->GetPosition()));

	if (ShouldResetCursorOffset())
		cursorOffset = targetPosition - transform->GetPosition();

	transform->SetPosition(targetPosition - cursorOffset);
}

plane SceneEditor::GetFloorPlane(const vec3& objectPosition) const
{
	return plane(vec3(0, objectPosition.y, 0), FSMath::Up);
}

plane SceneEditor::GetVerticalPlane(const vec3& objectPosition) const
{
	auto cameraDirection = vec3(camera->GetForward().x, 0, -camera->GetForward().z);
	return plane(objectPosition, cameraDirection);
}

vec3 SceneEditor::CalculatePositionAlongPlane(const plane& plane) const
{
	auto cursorRay = camera->GetCursorRay();

	auto distance = FSMath::RayIntersectPlaneDistance(plane, cursorRay);
	return vec3(cursorRay.origin + (cursorRay.direction * distance));
}

vec3 SceneEditor::CalculateVerticalPositionAlongPlane(const plane& plane) const
{
	auto position = CalculatePositionAlongPlane(plane);
	return vec3(0, position.y, 0);
}

bool SceneEditor::ShouldResetCursorOffset() const
{
	return  systems->input->IsButtonPressed(SDL_BUTTON_LEFT) ||
			systems->input->IsButtonPressed(SDL_SCANCODE_LSHIFT) ||
			systems->input->IsButtonReleased(SDL_SCANCODE_LSHIFT);
}
