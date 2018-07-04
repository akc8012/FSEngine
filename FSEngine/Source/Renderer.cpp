#include "../Header/Renderer.h"

Renderer::Renderer(FileSystem* fileSystem, Window* window, ShaderProgram* shaderProgram)
{
	this->window = window;
	this->shaderProgram = shaderProgram;
	camera = new Camera(fileSystem, window);
}

void Renderer::StartRender(Uint32 deltaTime)
{
	ClearScreen();
	shaderProgram->Use();

	camera->Update(deltaTime);
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	SetCameraMatrices();

	gameObject->GetComponent<TextureComponent>()->Bind();
	gameObject->GetComponent<RenderComponent>()->BindVertexArray();
	shaderProgram->SetMatrix("model", gameObject->GetComponent<TransformComponent>()->GetMatrix());

	DrawTriangles(gameObject->GetComponent<RenderComponent>()->GetTriangleCount());
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

void Renderer::SetCameraMatrices()
{
	if (shaderProgram->RenderPerspective())
		shaderProgram->SetMatrix("view", camera->GetComponent<TransformComponent>()->GetMatrix());

	mat4 projection = shaderProgram->RenderPerspective() ? camera->GetProjectionPerspective() : camera->GetProjectionOrthographic();
	shaderProgram->SetMatrix("projection", projection);
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
