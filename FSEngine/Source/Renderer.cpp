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

	TransformComponent* viewComponent = camera->GetComponent<TransformComponent>("View");
	systems->shaderProgram->SetMatrixUniform("viewMatrix", viewComponent->GetMatrix());
	systems->shaderProgram->SetVectorUniform("viewPosition", viewComponent->GetPosition());
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

	bool enableDepthTest = shading->GetParameterCollection()->GetParameter(ShadingComponent::EnableDepthTest);
	if (!systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::EnableDepthTest, enableDepthTest))
	{
		enableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::EnableDepthTest, enableDepthTest);
	}

	bool renderPerspective = shading->GetParameterCollection()->GetParameter(ShadingComponent::RenderPerspective);
	if (!systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::RenderPerspective, renderPerspective))
	{
		TransformComponent* projectionTransform = camera->GetComponent<TransformComponent>(renderPerspective ? "Perspective" : "Orthographic");
		systems->shaderProgram->SetMatrixUniform("projectionMatrix", projectionTransform->GetMatrix());

		systems->shaderProgram->SetBoolUniform("renderPerspective", renderPerspective);
		systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::RenderPerspective, renderPerspective);
	}

	systems->shaderProgram->SetVectorUniform("flatColor", shading->GetFlatColor());
	shading->BindTexture();

	mesh->BindVertexArray();
	mesh->DrawMesh();
}

void Renderer::EndRender(Window* window)
{
	window->SwapWindow();
}

Renderer::~Renderer()
{

}
