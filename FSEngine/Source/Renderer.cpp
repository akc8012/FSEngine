#include "../Header/Renderer.h"

Renderer::Renderer(FileSystem* fileSystem, Window* window, ShaderProgram* shaderProgram)
{
	this->window = window;
	this->shaderProgram = shaderProgram;
}

void Renderer::SetCamera(GameObject* camera)
{
	this->camera = camera;
}

void Renderer::StartRender(float deltaTime)
{
	ClearScreen();




	if (shaderProgram->RenderPerspective())
	{
		shaderProgram->SetMatrixUniform("viewMatrix", camera->GetComponent<TransformComponent>("View")->GetMatrix());
		shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<TransformComponent>("Perspective")->GetMatrix());
	}
	else
		shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<TransformComponent>("Orthographic")->GetMatrix());

	shaderProgram->SetVectorUniform("viewPosition", camera->GetComponent<TransformComponent>("View")->GetPosition());
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
	shaderProgram->SetMatrixUniform("modelMatrix", gameObject->GetComponent<TransformComponent>()->GetMatrix());
	shaderProgram->SetMatrixUniform("normalMatrix", gameObject->GetComponent<TransformComponent>()->CalculateNormalMatrix());

	gameObject->GetComponent<ShadingComponent>()->Use(shaderProgram);
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

		shadingComponent->Use(shaderProgram);
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

void Renderer::EndRender()
{
	window->SwapWindow();
}

Renderer::~Renderer()
{

}
