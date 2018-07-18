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
	camera->Update(deltaTime);
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	SetCameraMatrices();

	gameObject->GetComponent<TextureComponent>()->BindTexture();

	MeshComponent* mesh = gameObject->GetComponent<MeshComponent>();
	mesh->BindVertexArray();

	SetModelMatrices(gameObject->GetComponent<TransformComponent>());

	DrawTriangleArrays(mesh->GetVerticeCount());
}

void Renderer::RenderModel(GameObject* model)
{
	SetCameraMatrices();

	glEnable(GL_CULL_FACE);
	for (auto& meshComponent : *model->GetComponents<MeshComponent>())
	{
		ActivateAndBindTextures(meshComponent.second, *model->GetComponents<TextureComponent>());
		meshComponent.second->BindVertexArray();

		SetModelMatrices(model->GetComponent<TransformComponent>());
		DrawTriangleElements(meshComponent.second->GetIndiceCount());
	}

	glDisable(GL_CULL_FACE);
}

void Renderer::ActivateAndBindTextures(const MeshComponent* meshComponent, const unordered_map<string, TextureComponent*>& textureComponents)
{
	for (const auto& associatedTextureName : meshComponent->GetAssociatedTextureNames())
	{
		TextureComponent* texture = textureComponents.at(associatedTextureName);
		if (texture->GetTextureType() != TextureComponent::Diffuse)
			continue;

		texture->BindTexture();
	}
}

void Renderer::EndRender()
{
	window->SwapWindow();
}

void Renderer::ClearScreen()
{
	vec3 color = vec3(41, 48, 61);
	color /= 255;

	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetCameraMatrices()
{
	if (shaderProgram->RenderPerspective())
		shaderProgram->SetMatrix("view", camera->GetComponent<TransformComponent>("View")->GetMatrix());

	mat4 projection = shaderProgram->RenderPerspective() ? camera->GetComponent<TransformComponent>("Perspective")->GetMatrix() : camera->GetComponent<TransformComponent>("Orthographic")->GetMatrix();
	shaderProgram->SetMatrix("projection", projection);

	shaderProgram->SetVector("viewPosition", camera->GetComponent<TransformComponent>("View")->GetPosition());
}

void Renderer::SetModelMatrices(TransformComponent* transform)
{
	shaderProgram->SetMatrix("model", transform->GetMatrix());
	shaderProgram->SetMatrix("normalMatrix", transform->CalculateNormalMatrix());
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

Renderer::~Renderer()
{
	delete camera;
}
