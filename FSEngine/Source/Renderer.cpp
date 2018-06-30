#include "../Header/Renderer.h"

Renderer::Renderer(Window* window, ShaderProgram* shaderProgram)
{
	this->window = window;
	this->shaderProgram = shaderProgram;
	camera = new Camera(window);
}

void Renderer::StartRender(Uint32 deltaTime)
{
	ClearScreen();
	shaderProgram->Use();

	camera->Update(deltaTime);
	shaderProgram->SetMatrix("view", camera->GetTransformComponent()->GetMatrix());
	shaderProgram->SetMatrix("projection", camera->GetProjectionMatrix());
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	gameObject->GetRenderComponent()->BindTextures();
	gameObject->GetRenderComponent()->BindVertexArray();
	shaderProgram->SetMatrix("model", gameObject->GetTransformComponent()->GetMatrix());

	DrawTriangles(gameObject->GetRenderComponent()->GetTriangleCount());
}

void Renderer::EndRender()
{
	window->SwapWindow();
}

void Renderer::ClearScreen()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawTriangles(Uint32 triangleCount)
{
	const int First = 0;
	glDrawArrays(GL_TRIANGLES, First, triangleCount);
}

Renderer::~Renderer()
{
	delete camera;
}
