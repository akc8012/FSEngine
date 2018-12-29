#pragma once
#include "IEventListener.h"
#include "ShaderProgram.h"
#include "Systems.h"
#include "Window.h"
#include "GameObject.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

class Renderer : public IEventListener
{
private:
	enum Parameters { EnableDepthTest, RenderPerspective, CalculateLighting, Blend, ParametersLength };
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	unique_ptr<ShaderProgram> shaderProgram;
	Systems* systems = nullptr;
	IGameObject* camera = nullptr;

	void ClearScreen();
	void StartImGuiFrame(Window* window);
	void SetViewMatrices(Transform* viewTransform);

	void DrawGrid();
	void SetRenderParametersForGrid();

	void SetTransformMatrices(Transform* transform);

	void SetShadingParameters(const Shading* shading);
	void ApplyShading(Shading* shading);

	void SetDepthTest(bool enableDepthTest);
	void SetRenderPerspective(bool enableDepthTest);
	void SetCalculateLighting(bool calculateLighting);
	void SetBlend(bool blend);

	void DrawMesh(Mesh* mesh);
	void DrawTriangleElements(const Mesh* mesh);
	void DrawTriangleArrays(const Mesh* mesh);

public:
	Renderer(Systems* systems, IGameObject* camera);
	~Renderer();

	void ReCompileShaders();
	void ReceiveEvent(const string& key, const json& event) override;

	void StartRender(Window* window);
	void RenderGameObject(IGameObject* gameObject);
	void EndRender(Window* window);
};
