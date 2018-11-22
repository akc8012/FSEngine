#pragma once
#include "Scene.h"
#include "ClickLabel.h"

class ClickLabelManager
{
private:
	Scene* scene = nullptr;
	Systems* systems = nullptr;

	ClickLabel* activeClickLabel = nullptr;
	vector<ClickLabel*> clickLabels;

	ClickLabel* CreateClickLabelForGameObject(IGameObject* gameObject);
	ClickLabel* GetCursorIntersectingClickLabel() const;

public:
	ClickLabelManager(Scene* scene, Systems* systems);

	void CreateClickLabels();
	void Update();
};
