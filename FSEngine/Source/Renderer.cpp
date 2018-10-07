#include "../Header/Renderer.h"

Renderer::Renderer(Systems* systems, Components* components)
{
	this->systems = systems;
	this->components = components;
}

#pragma region StartRender
void Renderer::StartRender()
{
	ClearScreen();

	SetViewMatrices(components->transform->Get("Camera", "View"));

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

void Renderer::SetViewMatrices(Transform* viewTransform)
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

	systems->shaderProgram->SetMatrixUniform("modelMatrix", FSMath::IdentityMatrix);
	systems->shaderProgram->SetMatrixUniform("normalMatrix", FSMath::IdentityMatrix);
	systems->shaderProgram->SetVectorUniform("flatColor", vec4(1, 1, 0.6f, 1));
	systems->shaderProgram->SetMatrixUniform("projectionMatrix", components->transform->Get("Camera", "Perspective")->GetMatrix());
	systems->shaderProgram->SetBoolUniform("renderPerspective", true);
}
#pragma endregion

#pragma region RenderGameObject
void Renderer::RenderGameObject(const string& name)
{
	SetTransformMatrices(components->transform->Get(name));

	for (auto& mesh : components->mesh->GetComponents(name))
	{
		vector<string> textureNames = mesh->GetAssociatedTextureNames();
		if (textureNames.size() != 0)
			SetShadingParameters(components->shading->Get(name, textureNames.front()));
		else
			SetShadingParameters(components->shading->Get(name));

		DrawMesh(mesh);
	}
}

void Renderer::SetTransformMatrices(Transform* transform)
{
	systems->shaderProgram->SetMatrixUniform("modelMatrix", transform->GetMatrix());
	systems->shaderProgram->SetMatrixUniform("normalMatrix", transform->CalculateNormalMatrix());
}

void Renderer::SetShadingParameters(Shading* shading)
{
	SetDepthTest(shading->GetParameterCollection()->GetParameter(Shading::EnableDepthTest));
	SetRenderPerspective(shading->GetParameterCollection()->GetParameter(Shading::RenderPerspective));
	SetBlend(shading->GetParameterCollection()->GetParameter(Shading::Blend));

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

	Transform* projectionTransform = components->transform->Get("Camera", renderPerspective ? "Perspective" : "Orthographic");
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

void Renderer::DrawMesh(Mesh* mesh)
{
	mesh->BindVertexArray();

	mesh->GetParameterCollection()->GetParameter(Mesh::RenderBackfaces) ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
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
