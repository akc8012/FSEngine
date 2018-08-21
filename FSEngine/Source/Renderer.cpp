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
	systems->shaderProgram->SetMatrixUniform("modelMatrix", gameObject->GetComponent<TransformComponent>()->GetMatrix());
	systems->shaderProgram->SetMatrixUniform("normalMatrix", gameObject->GetComponent<TransformComponent>()->CalculateNormalMatrix());

	gameObject->GetComponent<ShadingComponent>()->Use(systems->shaderProgram);
	gameObject->GetComponent<MeshComponent>()->BindVertexArray(); // Use();
	DrawTriangleArrays(gameObject->GetComponent<MeshComponent>()->GetVerticeCount());
}

void Renderer::UseMeshAssociatedTextures(const MeshComponent* meshComponent, const unordered_map<string, ShadingComponent*>& shadingComponents)
{
	for (const auto& associatedTextureName : meshComponent->GetAssociatedTextureNames())
	{
		ShadingComponent* shadingComponent = shadingComponents.at(associatedTextureName);
		if (!shadingComponent->CanUse())
			continue;

		shadingComponent->Use(systems->shaderProgram);
	}
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
