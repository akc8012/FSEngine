#include "../Header/Renderer.h"

Renderer::Renderer(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
	camera = new Camera();
	SetFragmentMixUniforms();

	uniformLocations["model"] = shaderProgram->GetUniformLocation("model");
	uniformLocations["view"] = shaderProgram->GetUniformLocation("view");
	uniformLocations["projection"] = shaderProgram->GetUniformLocation("projection");
}

void Renderer::SetFragmentMixUniforms()
{
	//to-do: move this logic to shaderprogram?
	shaderProgram->Use();

	int uniformValue = 0;
	shaderProgram->SetInt("texture1", uniformValue);
	shaderProgram->SetInt("texture2", uniformValue+1);
}

void Renderer::StartRender()
{
	ClearScreen();
	shaderProgram->Use();
}

void Renderer::RenderGameObject(GameObject* gameObject)
{
	gameObject->GetRenderComponent()->BindTextures();
	gameObject->GetRenderComponent()->BindVertexArray();
	shaderProgram->SetMatrix(uniformLocations["model"], gameObject->GetTransformComponent()->GetMatrix());
}

void Renderer::EndRender(Uint32 deltaTime, Window* window)
{
	camera->CalculateViewMatrix(deltaTime);
	camera->CalculateProjectionMatrix(window->GetWindowSize());

	shaderProgram->SetMatrix(uniformLocations["view"], camera->GetViewMatrix());
	shaderProgram->SetMatrix(uniformLocations["projection"], camera->GetProjectionMatrix());

	DrawTriangles(); //to-do: can this be moved to the end of RenderGameObject()?
	window->SwapWindow();
}

void Renderer::ClearScreen()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawTriangles()
{
	const int First = 0, Count = 36;
	glDrawArrays(GL_TRIANGLES, 0, Count);
}

void Renderer::RecompileShaders()
{
	shaderProgram->CreateShaders();
	SetFragmentMixUniforms();
}

Renderer::~Renderer()
{
	delete camera;
}
