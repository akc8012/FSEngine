#include "../Header/SceneEditor.h"

SceneEditor::SceneEditor(Scene* scene, Systems* systems)
 : scene(scene)
{
	clickLabelManager = make_unique<ClickLabelManager>(scene, systems);
	InitializeEditor();
}

void SceneEditor::InitializeEditor()
{
	clickLabelManager->CreateClickLabels();
}

void SceneEditor::Update()
{
	clickLabelManager->Update();
}
