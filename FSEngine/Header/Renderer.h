#pragma once
#include "Systems.h"
#include "ComponentContainer.h"
#include "Window.h"
#include "GameObject.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

class Renderer
{
private:
	Systems* systems = nullptr;
	ComponentContainer* components = nullptr;

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
	Renderer(Systems* systems, ComponentContainer* components);
	~Renderer();

	void StartRender();
	void RenderGameObject(const string& name);
	void EndRender(Window* window);
};
