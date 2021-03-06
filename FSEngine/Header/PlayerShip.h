#pragma once
#include "GameObject.h"

class PlayerShip : public GameObject
{
private:
	Transform* transform = nullptr;

	vec3 direction;

	void ResetValues();
	void ControlShip();
	void SetCamera();

	float GetFrameAdjustedSpeed() const;

public:
	PlayerShip();

	void Start() override;
	void Update() override;
	ComponentCollection<Mesh>* GetMeshCollection() const override;
	ComponentCollection<Texture>* GetTextureCollection() const override;

	string GetGameObjectType() const override;
};
