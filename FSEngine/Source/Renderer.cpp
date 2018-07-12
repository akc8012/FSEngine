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

void Renderer::RenderModel(Model* model)
{
	SetCameraMatrices();

	vector<MeshComponent*> meshComponents = model->GetMeshComponents();
	for (int i = 0; i < meshComponents.size(); i++)
	{
		MeshComponent* meshComponent = meshComponents[i];
		ActivateAndBindTextures(meshComponent, model->GetTextureComponents());

		meshComponent->BindVertexArray();

		TransformComponent transform;
		transform.SetScale(vec3(0.025f, 0.025f, 0.025f));
		transform.SetRotation(Timer::GetSeconds() * 0.4f, vec3(0.3f, 1, 0));
		transform.SetPosition(vec3(0, -0, 0));

		SetModelMatrices(&transform);

		DrawTriangleElements(meshComponent->GetIndiceCount());
	}
}

void Renderer::ActivateAndBindTextures(const MeshComponent* meshComponent, const vector<TextureComponent*> textureComponents)
{
	vector<int> textureIndices = meshComponent->GetAssociatedTextureIndices();
	for (int i = 0; i < textureIndices.size(); i++)
	{
		TextureComponent* texture = textureComponents[i];
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
		shaderProgram->SetMatrix("view", camera->GetComponent<TransformComponent>()->GetMatrix());

	mat4 projection = shaderProgram->RenderPerspective() ? camera->GetProjectionPerspective() : camera->GetProjectionOrthographic();
	shaderProgram->SetMatrix("projection", projection);

	shaderProgram->SetVector("viewPosition", camera->GetComponent<TransformComponent>()->GetPosition());
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
