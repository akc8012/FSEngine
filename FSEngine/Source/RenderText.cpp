#include "../Header/RenderText.h"

void RenderText::Start()
{
	AddComponent(make_shared<FontTexture>(), "Shading")->LoadFont("consola.ttf");
	AddComponent(make_shared<Transform2D>(), "Transform");
	AddComponent(make_shared<QuadMesh>());

	systems->eventSystem->AddListener("SurfaceSizeChanged", this);
	systems->eventSystem->AddListener("AfterSceneLoad", this);

	GetParameterCollection()->SetParameter(DoDraw, false);
	GetParameterCollection()->SetParameter(DoLateDraw, true);
}

void RenderText::Update()
{

}

void RenderText::SetText(const string& text)
{
	if (GetComponent<FontTexture>("Shading")->GetText() == text)
		return;

	GetComponent<FontTexture>("Shading")->GenerateFontTexture(text);
	GetComponent<Transform2D>("Transform")->SetTransform(surfaceSize, GetComponent<FontTexture>("Shading")->GetSurfaceSize());
}

void RenderText::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SurfaceSizeChanged" || key == "AfterSceneLoad")
	{
		if (key == "SurfaceSizeChanged")
			surfaceSize = vec2 { event[0], event[1] };

		GetComponent<Transform2D>("Transform")->SetTransform(surfaceSize, GetComponent<FontTexture>("Shading")->GetSurfaceSize());
	}
}

string RenderText::GetGameObjectType() const
{
	return "RenderText";
}
