#pragma once
#include "GameObject.h"

#define SOL_CHECK_ARGUMENTS 1
#include <sol.hpp>

class PlayerShip : public GameObject
{
private:
	Transform* transform = nullptr;
	sol::state lua;

	vec3 direction;

	void ResetValues();
	void ControlShip();
	void SetCamera();

	float GetFrameAdjustedSpeed() const;

public:
	PlayerShip();

	void Start() override;
	void SceneLoaded() override;
	void Update() override;

	ComponentCollection<Mesh>* GetMeshCollection() const override;
	ComponentCollection<Texture>* GetTextureCollection() const override;

	string GetGameObjectType() const override;
};
