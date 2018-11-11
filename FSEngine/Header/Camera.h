#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
private:
	tvec2<int> surfaceSize;
	vec3 position;
	vec3 direction;

	ray cursorRay;
	vec3 lastCursorPosition;

	void ResetViewTransform();

	mat4 CalculateViewMatrix(const vec3& forward) const;
	mat4 CalculateProjectionMatrixPerspective(const tvec2<int>& surfaceSize) const;
	mat4 CalculateProjectionMatrixOrthographic() const;

	void HandleDirection();
	void HandlePosition(const vec3& forward);

	vec3 GetDirectionDelta() const;
	vec3 GetPositionDelta(const vec3& forward, const vec3& cursorPosition) const;

	vec3 GetDirectionMouseInput() const;
	vec3 GetDirectionKeyInput() const;

	vec3 GetPositionMouseInput(const vec3& cursorPosition) const;
	vec3 GetPositionKeyInput(const vec3& right, const vec3& forward) const;
	vec3 GetCursorPositionAtRayIntersect() const;

	vec3 GetZoomInput(const vec3& forward) const;
	float GetHeightKeyboardInput() const;
	float GetHeightMouseInput() const;

	float ClampPitch(float pitch) const;

	vec3 ProjectCursorPositionToWorldDirection() const;
	vec2 GetDeviceNormalizedCursorPosition(const tvec2<int>& cursorPosition) const;

	float GetFrameAdjustedSpeed() const;

public:
	~Camera();

	void Start() override;
	void Update() override;

	void SetPosition(const vec3& position);
	void SetOrientation(const vec3& orientation);
	vec3 GetPosition() const;
	vec3 GetOrientation() const;

	vec3 GetForward() const;
	vec3 GetUp() const;
	vec3 GetRight() const;

	const ray& GetCursorRay() const;

	void ReceiveEvent(const string& key, const json& event) override;

	json GetJson() const override;
	void SetFromJson(const json& j) override;

	string GetGameObjectType() const override;
};
