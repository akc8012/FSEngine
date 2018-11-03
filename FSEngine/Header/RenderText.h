#pragma once
#include "GameObject.h"

class RenderText : public GameObject
{
private:
	vec2 surfaceSize;

public:
	~RenderText();

	void Start() override;
	void Update() override;
	void ReceiveEvent(const string& key, const json& event) override;

	void SetText(const string& text);

	string GetGameObjectType() const override;
};
