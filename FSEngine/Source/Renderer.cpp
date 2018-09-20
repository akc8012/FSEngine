#include "../Header/Renderer.h"

Renderer::Renderer(Systems* systems)
{
	this->systems = systems;
}

void Renderer::SetCamera(GameObject* camera)
{
	this->camera = camera;
}

#pragma region StartRender
void Renderer::StartRender()
{
	ClearScreen();

	SetViewMatrices(camera->GetComponent<TransformComponent>("View").get());

	if (systems->fileSystem->GetSettingsValue<bool>("DrawGrid"))
		DrawGrid();
}

void Renderer::ClearScreen()
{
	vec3 color = vec3(61, 54, 71);
	color /= 255;

	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewMatrices(TransformComponent* viewTransform)
{
	systems->shaderProgram->SetMatrixUniform("viewMatrix", viewTransform->GetMatrix());
	systems->shaderProgram->SetVectorUniform("viewPosition", viewTransform->GetPosition());
}

// https://www.opengl.org/discussion_boards/showthread.php/181622-OpenGL-Drawing-Grid-%28help%29
void Renderer::DrawGrid()
{
	SetRenderParametersForGrid();
	glBegin(GL_LINES);

	const int GridSize = 1000;
	int halfGridSize = GridSize / 2;

	for (int i = -halfGridSize; i <= halfGridSize; i++)
	{
		vec3 xLinePoint(i, 0, halfGridSize);
		glVertex3f(xLinePoint.x, xLinePoint.y, -xLinePoint.z);
		glVertex3f(xLinePoint.x, xLinePoint.y, xLinePoint.z);

		vec3 zLinePoint(halfGridSize, 0, i);
		glVertex3f(-zLinePoint.x, zLinePoint.y, zLinePoint.z);
		glVertex3f(zLinePoint.x, zLinePoint.y, zLinePoint.z);
	}

	glEnd();
}

void Renderer::SetRenderParametersForGrid()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	systems->shaderProgram->SetMatrixUniform("modelMatrix", TransformComponent::IdentityMatrix);
	systems->shaderProgram->SetMatrixUniform("normalMatrix", TransformComponent::IdentityMatrix);
	systems->shaderProgram->SetVectorUniform("flatColor", vec4(1, 1, 0.6f, 1));
	systems->shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<TransformComponent>("Perspective")->GetMatrix());
	systems->shaderProgram->SetBoolUniform("renderPerspective", true);
}
#pragma endregion

#pragma region RenderGameObject
void Renderer::RenderGameObject(const GameObject* gameObject)
{
	SetTransformMatrices(gameObject->GetComponent<TransformComponent>().get());

	for (auto& mesh : gameObject->GetComponents<MeshComponent>())
	{
		vector<string> textureNames = mesh.second->GetAssociatedTextureNames();
		if (textureNames.size() != 0)
			SetShadingParameters(gameObject->GetComponent<ShadingComponent>(textureNames.front()).get());
		else
			SetShadingParameters(gameObject->GetComponent<ShadingComponent>().get());

		DrawMesh(mesh.second.get());
	}
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
	SetBlend(shading->GetParameterCollection()->GetParameter(ShadingComponent::Blend));

	systems->shaderProgram->SetVectorUniform("flatColor", shading->GetFlatColor());
	shading->BindTexture();
}

void Renderer::SetDepthTest(bool enableDepthTest)
{
	if (systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::EnableDepthTest, enableDepthTest))
		return;

	enableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::EnableDepthTest, enableDepthTest);
}

void Renderer::SetRenderPerspective(bool renderPerspective)
{
	if (systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::RenderPerspective, renderPerspective))
		return;

	shared_ptr<TransformComponent> projectionTransform = camera->GetComponent<TransformComponent>(renderPerspective ? "Perspective" : "Orthographic");
	systems->shaderProgram->SetMatrixUniform("projectionMatrix", projectionTransform->GetMatrix());

	systems->shaderProgram->SetBoolUniform("renderPerspective", renderPerspective);
	systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::RenderPerspective, renderPerspective);
}

void Renderer::SetBlend(bool blend)
{
	if (systems->shaderProgram->GetParameterCollection()->IsInitializedAndEqualTo(ShaderProgram::Blend, blend))
		return;

	blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	systems->shaderProgram->GetParameterCollection()->SetParameter(ShaderProgram::Blend, blend);
}

void Renderer::DrawMesh(MeshComponent* mesh)
{
	mesh->BindVertexArray();

	mesh->GetParameterCollection()->GetParameter(MeshComponent::RenderBackfaces) ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
	mesh->DrawMesh();
}
#pragma endregion

#pragma region EndRender
void Renderer::EndRender(Window* window)
{
	window->SwapWindow();
}
#pragma endregion

Renderer::~Renderer()
{

}
