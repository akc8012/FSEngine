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

#include <string>

class Renderer
{
private:
	Systems* systems = nullptr;
	GameObject* camera = nullptr;

	void ClearScreen();

	void UseMeshAssociatedTextures(const MeshComponent* meshComponent, const unordered_map<string, ShadingComponent*>& shadingComponents);

	void DrawTriangleArrays(Uint32 verticeCount);
	void DrawTriangleElements(Uint32 indiceCount);

public:
	Renderer(Systems* systems);
	~Renderer();

	void SetCamera(GameObject* camera);

	void StartRender(float deltaTime);
	void RenderGameObject(GameObject* gameObject);
	void EndRender(Window* window);
};
