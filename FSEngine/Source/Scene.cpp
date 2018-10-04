#include "../Header/Scene.h"

Scene::Scene(const string& name, Systems* systems, Window* window)
{
	this->name = name;
	this->systems = systems;
	this->window = window;

	components = make_unique<Components>();
	gameObjectContainer = make_unique<GameObjectContainer>(systems, components.get());

	AddGameObjects(window);
}

void Scene::AddGameObjects(Window* window)
{
	auto gameObject = gameObjectContainer->AddGameObject("MemeFaceCube", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Texture>("Resource/Image/awesomeface.png"));
	components->transform->Get(gameObject->GetName())->SetPosition(4.5f, 0.2f, 0);

	gameObject = gameObjectContainer->AddGameObject("GreenCube", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.1f, 0.6f, 0.3f));
	components->transform->Get(gameObject->GetName())->SetPosition(6, -0.2f, 0.1f);
	components->transform->Get(gameObject->GetName())->SetScale(2, 0.8f, 2.8f);

	gameObject = gameObjectContainer->AddGameObject("Red", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.8f, 0.f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(1.5f, 1, -3);

	gameObject = gameObjectContainer->AddGameObject("Green", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.f, 0.8f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(1, -1, -1);

	gameObject = gameObjectContainer->AddGameObject("Blue", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.f, 0.f, 0.8f));
	components->transform->Get(gameObject->GetName())->SetPosition(-0.8f, 0, -2);

	gameObject = gameObjectContainer->AddGameObject("Yellow", new CubePrimitive());
	components->shading->Add(gameObject->GetName(), make_shared<Shading>(0.6f, 0.6f, 0.f));
	components->transform->Get(gameObject->GetName())->SetPosition(-2, -1, 0);

	for (int i = 0; i < 100; i++)
	{
		GameObject* cube = new CubePrimitive();
		gameObject = gameObjectContainer->AddGameObject(std::to_string(i), cube);
		components->shading->Add(gameObject->GetName(), make_shared<Shading>(systems->random->GetRandomUniformVector(0.f, 1.f)));
		components->transform->Get(gameObject->GetName())->SetPosition(systems->random->GetRandomUniformVector(-20.f, 20.f));
	}

	gameObject = gameObjectContainer->AddGameObject("DebugText", new RenderText(window));
	RenderText* debugText = dynamic_cast<RenderText*>(gameObject);
	debugText->SetText("Debug text");
	debugText->GetParameterCollection()->SetParameter(GameObject::DoLateUpdate, true);
	debugText->GetParameterCollection()->SetParameter(GameObject::DoLateDraw, true);
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	gameObjectContainer->AddGameObject("Camera", new Camera(window));
	gameObjectContainer->AddGameObject("PlayerShip", new PlayerShip());
}

void Scene::LoadScene()
{
	json j = json::parse(FileSystem::LoadTextFromFile(GetFileName()));

	for (const auto& gameObject : gameObjectContainer->GetGameObjects())
		gameObject->SetFromJson(j[gameObject->GetName()]);
}

void Scene::SaveScene() const
{
	json j;
	for (const auto& gameObject : gameObjectContainer->GetGameObjects())
		j[gameObject->GetName()] = gameObject->GetJson();

	FileSystem::WriteTextToFile(j.dump(2), GetFileName());
}

string Scene::GetFileName() const
{
	return "Resource/Json/" + name + ".json";
}

GameObjectContainer* Scene::GetGameObjectContainer() const
{
	return gameObjectContainer.get();
}

Components* Scene::GetComponents() const
{
	return components.get();
}

Scene::~Scene()
{
	//SaveScene();
}
