#pragma once
#include "GameObject.h"
#include "ClickLabel.h"

class ClickLabelManager : public GameObject
{
private:
	vector<ClickLabel*> clickLabels;

	ClickLabel* CreateClickLabelForGameObject(IGameObject* gameObject);

public:
	void Start() override;
	void SceneLoaded() override;

	string GetGameObjectType() const override;
};
