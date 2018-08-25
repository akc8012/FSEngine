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
	SetViewMatrices(camera->GetComponent<TransformComponent>("View"));
}

void Renderer::ClearScreen()
{
	vec3 color = vec3(41, 48, 61);
	color /= 255;

	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewMatrices(TransformComponent* viewTransform)
{
	systems->shaderProgram->SetMatrixUniform("viewMatrix", viewTransform->GetMatrix());
	systems->shaderProgram->SetVectorUniform("viewPosition", viewTransform->GetPosition());
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	SetTransformMatrices(gameObject->GetComponent<TransformComponent>());

	SetShadingParameters(gameObject->GetComponent<ShadingComponent>());

	RenderMesh(gameObject->GetComponent<MeshComponent>());
}

void Renderer::SetTransformMatrices(TransformComponent* transform)
{
	systems->shaderProgram->SetMatrixUniform("modelMatrix", transform->GetMatrix());
	systems->shaderProgram->SetMatrixUniform("normalMatrix", transform->CalculateNormalMatrix());
}

void Renderer::SetShadingParameters(ShadingComponent* shading)
{
	SetDepthTest(shading->GetParameterCollection()->GetParameter(ShadingComponent::EnableDepthTest));
	SetRenderPerspective(shading->GetParameterCollection()->GetParameter(ShadingComponent::RenderPerspective));

	systems->shaderProgram->SetVectorUniform("flatColor", shading->GetFlatColor());
	shading->BindTexture();
}

void Renderer::SetDepthTest(bool enableDepthTest)
{
	if (!systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::EnableDepthTest, enableDepthTest))
	{
		enableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::EnableDepthTest, enableDepthTest);
	}
}

void Renderer::SetRenderPerspective(bool renderPerspective)
{
	if (!systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::RenderPerspective, renderPerspective))
	{
		TransformComponent* projectionTransform = camera->GetComponent<TransformComponent>(renderPerspective ? "Perspective" : "Orthographic");
		systems->shaderProgram->SetMatrixUniform("projectionMatrix", projectionTransform->GetMatrix());

		systems->shaderProgram->SetBoolUniform("renderPerspective", renderPerspective);
		systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::RenderPerspective, renderPerspective);
	}
}

void Renderer::RenderMesh(MeshComponent* mesh)
{
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
