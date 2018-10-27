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
	enum Parameters
	{
		EnableDepthTest,
		RenderPerspective,
		Blend,

		ParametersLength
	};

	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	Systems* systems = nullptr;
	IGameObject* camera = nullptr;

	void ClearScreen();
	void SetViewMatrices(Transform* viewTransform);

	void DrawGrid();
	void SetRenderParametersForGrid();

	void SetTransformMatrices(Transform* transform);

	Drawable* FindDrawable(const IGameObject* gameObject, const vector<string>& textureNames) const;
	void SetDrawableParameters(Drawable* drawable);

	void SetDepthTest(bool enableDepthTest);
	void SetRenderPerspective(bool enableDepthTest);
	void SetBlend(bool blend);

	void DrawMesh(Mesh* mesh);

public:
	Renderer(Systems* systems, IGameObject* camera);
	~Renderer();

	void StartRender();
	void RenderGameObject(IGameObject* gameObject);
	void EndRender(Window* window);
};
