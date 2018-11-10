#include "../Header/Renderer.h"

Renderer::Renderer(Systems* systems, IGameObject* camera)
 : systems(systems), camera(camera)
{
	shaderProgram = make_unique<ShaderProgram>();

	string parameterNames[] = { "EnableDepthTest", "RenderPerspective", "CalculateLighting", "Blend" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);

	systems->eventSystem->AddListener("SurfaceSizeChanged", this);
	systems->eventSystem->AddListener("WindowFocusGained", this);
}

void Renderer::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SurfaceSizeChanged")
		parameterCollection->ReInitializeParameters();

	if (key == "WindowFocusGained" && systems->fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
		ReCompileShaders();
}

void Renderer::ReCompileShaders()
{
	shaderProgram->CompileShaders();
	parameterCollection->ReInitializeParameters();
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
	json backgroundSetting = systems->fileSystem->GetSettingsValue("BackgroundColor");
	vec3 backgroundColor = vec3(backgroundSetting[0], backgroundSetting[1], backgroundSetting[2]) / 255.f;

	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewMatrices(Transform* viewTransform)
{
	shaderProgram->SetMatrixUniform("viewMatrix", viewTransform->GetMatrix());
	shaderProgram->SetVectorUniform("viewPosition", viewTransform->GetPosition());
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
	shaderProgram->SetMatrixUniform("modelMatrix", FSMath::IdentityMatrix);
	shaderProgram->SetMatrixUniform("normalMatrix", FSMath::IdentityMatrix);

	SetDepthTest(true);
	SetRenderPerspective(true);
	SetCalculateLighting(false);
	SetBlend(true);

	shaderProgram->SetVectorUniform("flatColor", vec4(0.8f, 0.8f, 0.4f, 1));
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
	shaderProgram->SetMatrixUniform("modelMatrix", transform->GetMatrix());
	shaderProgram->SetMatrixUniform("normalMatrix", transform->CalculateNormalMatrix());
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
	SetCalculateLighting(shadingParameters->GetParameter(Shading::CalculateLighting));
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
	shaderProgram->SetMatrixUniform("projectionMatrix", projectionTransform->GetMatrix());

	shaderProgram->SetBoolUniform("renderPerspective", renderPerspective);
	parameterCollection->SetParameter(RenderPerspective, renderPerspective);
}

void Renderer::SetCalculateLighting(bool calculateLighting)
{
	if (parameterCollection->IsInitializedAndEqualTo(CalculateLighting, calculateLighting))
		return;

	shaderProgram->SetBoolUniform("calculateLighting", calculateLighting);
	parameterCollection->SetParameter(CalculateLighting, calculateLighting);
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
	shaderProgram->SetVectorUniform("flatColor", shading->GetColor());
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
	systems->eventSystem->RemoveListener(this);
}
