#pragma once
#include "Systems.h"
#include "Window.h"
#include "GameObject.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class Renderer
{
private:
	Systems* systems = nullptr;
	GameObject* camera = nullptr;

	void ClearScreen();
	void SetViewMatrices(TransformComponent* viewTransform);

	void SetTransformMatrices(TransformComponent* transform);

	void SetShadingParameters(ShadingComponent* shading);
	void SetDepthTest(bool enableDepthTest);
	void SetRenderPerspective(bool enableDepthTest);
	void SetBlend(bool blend);

	void RenderMesh(MeshComponent* mesh);

public:
	Renderer(Systems* systems);
	~Renderer();

	void SetCamera(GameObject* camera);

	void StartRender();
	void RenderGameObject(GameObject* gameObject);
	void EndRender(Window* window);
};
