#include "../Header/Renderer.h"

Renderer::Renderer(FileSystem* fileSystem, Window* window, ShaderProgram* shaderProgram, Input* input)
{
	this->window = window;
	this->shaderProgram = shaderProgram;
	camera = new Camera(fileSystem, input, window);
}

void Renderer::StartRender(float deltaTime)
{
	ClearScreen();
	shaderProgram->Use();

	camera->Update(deltaTime);
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	SetCameraMatrices();

	gameObject->GetComponent<TextureComponent>()->BindTexture();
	gameObject->GetComponent<RenderComponent>()->BindVertexArray();
	shaderProgram->SetMatrix("model", gameObject->GetComponent<TransformComponent>()->GetMatrix());

	DrawTriangleArrays(gameObject->GetComponent<RenderComponent>()->GetTriangleCount());
}

void Renderer::RenderModel(Model* model)
{
	SetCameraMatrices();

	for (const auto& meshComponent : model->GetMeshComponents())
	{
		// bind texture
		meshComponent->BindVertexArray();

		TransformComponent transform;
		transform.SetPosition(vec3(0, -0.8f, 0));
		transform.SetScale(vec3(0.1f, 0.1f, 0.1f));
		shaderProgram->SetMatrix("model", transform.GetMatrix());

		DrawTriangleElements(meshComponent->GetIndiceCount());
	}
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

void Renderer::DrawTriangleArrays(Uint32 triangleCount)
{
	const int First = 0;
	glDrawArrays(GL_TRIANGLES, First, triangleCount);
}

void Renderer::DrawTriangleElements(Uint32 indiceCount)
{
	const int Offset = 0;
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, Offset);
}

Renderer::~Renderer()
{
	delete camera;
}
