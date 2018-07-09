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

	auto meshComponents = model->GetMeshComponents();
	for (int i = 0; i < meshComponents.size(); i++)
	{
		ActivateAndBindTextures(i, model);
		meshComponents[i]->BindVertexArray();

		TransformComponent transform;
		transform.SetPosition(vec3(0.4f, -0.8f, 1.5f));
		transform.SetScale(vec3(0.1f, 0.1f, 0.1f));
		transform.SetRotation(Timer::GetSeconds() * radians(25.f), vec3(0, 1, 0));\

		SetModelMatrices(&transform);

		DrawTriangleElements(meshComponents[i]->GetIndiceCount());
	}
}

void Renderer::ActivateAndBindTextures(int meshIndex, const Model* model)
{
	using std::get;

	auto textureComponents = model->GetTextureComponents();
	for (int i = 0; i < textureComponents.size(); i++)
	{
		bool isOnMeshIndex = get<Model::MeshIndex>(textureComponents[i]) == meshIndex;
		if (!isOnMeshIndex)
			continue;

		TextureComponent* texture = get<Model::TextureIndex>(textureComponents[i]);
		TextureComponent::TextureType textureType = texture->GetTextureType();
		if (textureType == TextureComponent::Specular)
			continue;

		glActiveTexture(GL_TEXTURE0 + textureType == TextureComponent::Diffuse ? 0 : 1);
		texture->BindTexture();
	}

	glActiveTexture(GL_TEXTURE0);
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
