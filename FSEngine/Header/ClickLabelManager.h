#pragma once
#include "GameObject.h"
#include "ClickLabel.h"

class ClickLabelManager : public GameObject
{
private:
	ClickLabel* activeClickLabel = nullptr;
	vector<ClickLabel*> clickLabels;

	ClickLabel* CreateClickLabelForGameObject(IGameObject* gameObject);
	ClickLabel* GetCursorIntersectingClickLabel() const;

public:
	void Start() override;
	void SceneLoaded() override;
	void Update() override;

	string GetGameObjectType() const override;
};
