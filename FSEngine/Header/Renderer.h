#pragma once
#include "Systems.h"
#include "Window.h"
#include "GameObject.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

class Renderer
{
private:
	Systems* systems = nullptr;
	GameObject* camera = nullptr;

	void ClearScreen();
	void SetViewMatrices(Transform* viewTransform);

	void DrawGrid();
	void SetRenderParametersForGrid();

	void SetTransformMatrices(Transform* transform);

	void SetShadingParameters(Shading* shading);
	void SetDepthTest(bool enableDepthTest);
	void SetRenderPerspective(bool enableDepthTest);
	void SetBlend(bool blend);

	void DrawMesh(Mesh* mesh);

public:
	Renderer(Systems* systems);
	~Renderer();

	void SetCamera(GameObject* camera);

	void StartRender();
	void RenderGameObject(const GameObject* gameObject);
	void EndRender(Window* window);
};
