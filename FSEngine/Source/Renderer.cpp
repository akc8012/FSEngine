#include "../Header/Renderer.h"

Renderer::Renderer(Systems* systems)
{
	this->systems = systems;
}

void Renderer::SetCamera(GameObject* camera)
{
	this->camera = camera;
}

void Renderer::StartRender(float deltaTime)
{
	ClearScreen();

	if (systems->shaderProgram->RenderPerspective())
	{
		systems->shaderProgram->SetMatrixUniform("viewMatrix", camera->GetComponent<TransformComponent>("View")->GetMatrix());
		systems->shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<TransformComponent>("Perspective")->GetMatrix());
	}
	else
		systems->shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<TransformComponent>("Orthographic")->GetMatrix());

	systems->shaderProgram->SetVectorUniform("viewPosition", camera->GetComponent<TransformComponent>("View")->GetPosition());
}

void Renderer::ClearScreen()
{
	vec3 color = vec3(41, 48, 61);
	color /= 255;

	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	TransformComponent* transform = gameObject->GetComponent<TransformComponent>();
	ShadingComponent* shading = gameObject->GetComponent<ShadingComponent>();
	MeshComponent* mesh = gameObject->GetComponent<MeshComponent>();

	systems->shaderProgram->SetMatrixUniform("modelMatrix", transform->GetMatrix());
	systems->shaderProgram->SetMatrixUniform("normalMatrix", transform->CalculateNormalMatrix());

	// EXPENSIVE!!! Should only call these when a change has been registered. Also, we need to set camera stuff here.
	{
		shading->EnableDepthTest() ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		systems->shaderProgram->SetBoolUniform("renderPerspective", shading->GetRenderPerspective());
	}

	systems->shaderProgram->SetVectorUniform("flatColor", shading->GetFlatColor());
	shading->BindTexture();

	mesh->BindVertexArray();
	DrawTriangleArrays(mesh->GetVerticeCount()); // make this polymorphic / works also for model
}

void Renderer::DrawTriangleArrays(Uint32 verticeCount)
{
	const int First = 0;
	glDrawArrays(GL_TRIANGLES, First, verticeCount);
}

void Renderer::DrawTriangleElements(Uint32 indiceCount)
{
	const int Offset = 0;
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, Offset);
}

void Renderer::EndRender(Window* window)
{
	window->SwapWindow();
}

Renderer::~Renderer()
{

}
