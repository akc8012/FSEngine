#include "../Header/Renderer.h"

Renderer::Renderer(Systems* systems, IGameObject* camera)
 : systems(systems), camera(camera)
{
	string parameterNames[] = { "EnableDepthTest", "RenderPerspective", "Blend" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);
}

#pragma region StartRender
void Renderer::StartRender()
{
	ClearScreen();

	SetViewMatrices(camera->GetComponent<Transform>("View"));

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
	SetDepthTest(true);
	SetRenderPerspective(true);
	SetBlend(true);

	systems->shaderProgram->SetMatrixUniform("modelMatrix", FSMath::IdentityMatrix);
	systems->shaderProgram->SetMatrixUniform("normalMatrix", FSMath::IdentityMatrix);
	systems->shaderProgram->SetVectorUniform("flatColor", vec4(1, 1, 0.6f, 1));
	systems->shaderProgram->SetMatrixUniform("projectionMatrix", camera->GetComponent<Transform>("Perspective")->GetMatrix());
	systems->shaderProgram->SetBoolUniform("renderPerspective", true);
}
#pragma endregion

#pragma region RenderGameObject
void Renderer::RenderGameObject(IGameObject* gameObject)
{
	SetTransformMatrices(gameObject->GetComponent<Transform>());

	Model* model = gameObject->TryGetComponent<Model>();
	bool hasModel = model != nullptr;

	for (auto mesh : hasModel ? model->GetMeshCollection()->GetComponents() : gameObject->GetComponentContainer()->GetComponents<Mesh>())
	{
		auto shading = hasModel ? FindShading(model, mesh->GetAssociatedTextureNames()) : gameObject->GetComponent<Shading>();

		SetShadingParameters(shading);
		ApplyShading(shading);

		DrawMesh(mesh);
	}
}

void Renderer::SetTransformMatrices(Transform* transform)
{
	systems->shaderProgram->SetMatrixUniform("modelMatrix", transform->GetMatrix());
	systems->shaderProgram->SetMatrixUniform("normalMatrix", transform->CalculateNormalMatrix());
}

Shading* Renderer::FindShading(const Model* model, const vector<string>& textureNames) const
{
	return model->GetTextureCollection()->Get(textureNames.front());
}

void Renderer::SetShadingParameters(const Shading* shading)
{
	auto shadingParameters = shading->GetParameterCollection();

	SetDepthTest(shadingParameters->GetParameter(Shading::EnableDepthTest));
	SetRenderPerspective(shadingParameters->GetParameter(Shading::RenderPerspective));
	SetBlend(shadingParameters->GetParameter(Shading::Blend));
}

void Renderer::SetDepthTest(bool enableDepthTest)
{
	if (parameterCollection->IsInitializedAndEqualTo(EnableDepthTest, enableDepthTest))
		return;

	enableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	parameterCollection->SetParameter(EnableDepthTest, enableDepthTest);
}

void Renderer::SetRenderPerspective(bool renderPerspective)
{
	if (parameterCollection->IsInitializedAndEqualTo(RenderPerspective, renderPerspective))
		return;

	Transform* projectionTransform = camera->GetComponent<Transform>(renderPerspective ? "Perspective" : "Orthographic");
	systems->shaderProgram->SetMatrixUniform("projectionMatrix", projectionTransform->GetMatrix());

	systems->shaderProgram->SetBoolUniform("renderPerspective", renderPerspective);
	parameterCollection->SetParameter(RenderPerspective, renderPerspective);
}

void Renderer::SetBlend(bool blend)
{
	if (parameterCollection->IsInitializedAndEqualTo(Blend, blend))
		return;

	blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	parameterCollection->SetParameter(Blend, blend);
}

void Renderer::ApplyShading(Shading* shading)
{
	systems->shaderProgram->SetVectorUniform("flatColor", shading->GetColor());
	shading->BindTexture();
}

void Renderer::DrawMesh(Mesh* mesh)
{
	mesh->BindVertexArray();

	mesh->GetParameterCollection()->GetParameter(Mesh::RenderBackfaces) ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
	mesh->GetParameterCollection()->GetParameter(Mesh::DrawElements) ? DrawTriangleElements(mesh) : DrawTriangleArrays(mesh);
}

void Renderer::DrawTriangleElements(const Mesh* mesh)
{
	const int Offset = 0;
	glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, Offset);
}

void Renderer::DrawTriangleArrays(const Mesh* mesh)
{
	const int First = 0;
	glDrawArrays(GL_TRIANGLES, First, mesh->GetVerticeCount());
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
