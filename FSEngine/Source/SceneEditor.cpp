#include "../Header/SceneEditor.h"

SceneEditor::SceneEditor(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	clickLabelManager = make_unique<ClickLabelManager>(scene, systems);
	InitializeEditor();
}

void SceneEditor::InitializeEditor()
{
	clickLabelManager->CreateClickLabels();
	camera = scene->GetGameObjectContainer()->GetGameObjectAs<Camera>("Camera");
}

void SceneEditor::Update()
{
	clickLabelManager->Update();

	if (systems->input->IsButtonHeld(SDL_BUTTON_LEFT))
		TranslateActiveGameObject(clickLabelManager->GetActiveGameObject());
}

void SceneEditor::TranslateActiveGameObject(IGameObject* activeGameObject)
{
	if (activeGameObject == nullptr)
		return;

	auto transform = activeGameObject->GetComponent<Transform>();
	auto floorPlane = plane(vec3(0, transform->GetPosition().y, 0), FSMath::Up);
	auto cursorRay = camera->GetCursorRay();

	auto distance = FSMath::RayIntersectPlaneDistance(floorPlane, cursorRay);
	auto position = vec3(cursorRay.origin + (cursorRay.direction * distance));

	if (systems->input->IsButtonPressed(SDL_BUTTON_LEFT))
		cursorOffset = position - transform->GetPosition();

	transform->SetPosition(position - cursorOffset);
}
