#include "../Header/Renderer.h"

Renderer::Renderer(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
	SetFragmentMixUniforms();
}

void Renderer::SetFragmentMixUniforms()
{
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
	shaderProgram->SetMatrix("model", gameObject->GetTransformComponent()->GetMatrix());
}

void Renderer::EndRender(mat4 viewMatrix, Window* window)
{
	//to-do: extract this further into camera?
	SetViewMatrix(viewMatrix);
	SetProjectionMatrix(window->GetWindowSize());

	DrawTriangles(); //to-do: can this be moved to the end of RenderGameObject()?
	window->SwapWindow();
}

void Renderer::ClearScreen()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewMatrix(mat4 viewMatrix)
{
	shaderProgram->SetMatrix("view", viewMatrix);
}

void Renderer::SetProjectionMatrix(vec2 windowSize)
{
	const float FieldOfView = radians(45.0f);
	const float AspectRatio = (float)windowSize.x / (float)windowSize.y;
	const float NearPlane = 0.1f;
	const float FarPlane = 100.0f;
	mat4 projectionMatrix = perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);

	shaderProgram->SetMatrix("projection", projectionMatrix);
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

}
