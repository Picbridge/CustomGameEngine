#pragma once
class ServiceLocator
{
private:
	ServiceLocator() {};

	static ServiceLocator* instance;

	struct Services
	{
	public:
		WindowHandler& GetWindow() { return AWindow; }
		PhysicsManager* GetPhysicsSystem() { return Physics; }
		EventManager* GetEventSystem() { return Event; }
		InputManager* GetInputSystem() { return Input; }
		Renderer* GetRenderSystem() { return Render; }
		GameResourceFactory* GetGameResourceFactory() { return ResourceFactory; }
		GameObjectFactory* GetGameObjectFactory() { return ObjectFactory; }
		FrameRateController* GetFrameRateController() { return FrameRateControl; }
	private:
		WindowHandler& AWindow = WindowHandler::GetInstance();
		PhysicsManager* Physics = PhysicsManager::GetInstance();
		EventManager* Event = EventManager::GetInstance();
		InputManager* Input = InputManager::GetInstance();
		Renderer* Render = Renderer::GetInstance();
		FrameRateController* FrameRateControl = FrameRateController::GetInstance();
		GameResourceFactory* ResourceFactory = GameResourceFactory::GetInstance();
		GameObjectFactory* ObjectFactory = GameObjectFactory::GetInstance();
	};

public:
	static ServiceLocator* GetInstance();

	~ServiceLocator() {}
	Services EngineServices;
};

class Engine
{
public:
	static Engine* GetInstance();

	void Init();

	void SetWorld(std::vector<Scene*> scenes);
	void AddLevelToWorld(Scene* scene);
	void ChangeScene(Scene* scene);
	void PushScene(Scene* scene);
	void PopScene();
	void SceneLateUpdate();


	void HandleEvent(const Event& evt);
	void Update();
	void Draw();
	void PostUpdate();

	void Quit();

	bool IsRunning();

	std::string GetCurrentSceneFile() { return m_pCurScene->GetGameObjectFile(); }
private:
	static Engine* instance;

	Engine();
	Scene* m_pCurScene;
	std::stack<Scene*> sceneStack;
	bool m_isRunning;
	std::queue<int> m_changeSceneQueue;
	ServiceLocator* serviceLocator;

	struct World
	{
		std::vector<Scene*> Scenes;
	};

	World world;
	EventHandler m_sceneChangeCallback;
	int m_sceneChangeEventId;
};

