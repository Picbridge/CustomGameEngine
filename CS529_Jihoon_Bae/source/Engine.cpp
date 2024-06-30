#include "pch.h"

Engine* Engine::instance = nullptr;
ServiceLocator* ServiceLocator::instance = nullptr;

Engine* Engine::GetInstance()
{
    if (!instance) {
        instance = new Engine();
    }
    return instance;
}

Engine::Engine() : m_isRunning(true), m_pCurScene(nullptr), serviceLocator {ServiceLocator::GetInstance()} ,m_sceneChangeCallback([this](const Event& e) { HandleEvent(e); })
{
}

void Engine::Init()
{
    m_sceneChangeEventId = serviceLocator->EngineServices.GetEventSystem()->Subscribe(EventType::SceneChangeEvent, m_sceneChangeCallback);
    serviceLocator->EngineServices.GetWindow().Init();
    serviceLocator->EngineServices.GetInputSystem()->Init();
    serviceLocator->EngineServices.GetPhysicsSystem()->Init();
    serviceLocator->EngineServices.GetRenderSystem()->Init();

    //Resource Factory Init
    serviceLocator->EngineServices.GetPhysicsSystem()->SetGravity(0.0f);

    serviceLocator->EngineServices.GetGameResourceFactory()->StoreAllResources("data/ResourceData.json");

    std::cout << "Engine Initialized" << std::endl;
}

void Engine::SetWorld(std::vector<Scene*> scenes)
{
    world.Scenes = scenes;
}

void Engine::AddLevelToWorld(Scene* scene)
{
    world.Scenes.push_back(scene);
}

void Engine::ChangeScene(Scene* scene)
{
    if (scene == m_pCurScene)
    {
        std::cout << "Failed to switch the scene: Tried to switch to current scene"<< std::endl;
        return;
    }

    if (!sceneStack.empty())
    {
        sceneStack.top()->Destroy();
        sceneStack.pop();
    }

    sceneStack.push(scene);
    m_pCurScene = scene;
    m_pCurScene->Init();
}

void Engine::PushScene(Scene* scene)
{
    if (!sceneStack.empty())
        sceneStack.top()->Pause();

    sceneStack.push(scene);
}   

void Engine::PopScene()
{
    if (!sceneStack.empty())
    {
        sceneStack.top()->Destroy();
        sceneStack.pop();

        sceneStack.top()->Resume();
    }
}

void Engine::SceneLateUpdate()
{
    if (m_changeSceneQueue.size() > 0)
    {
        ChangeScene(world.Scenes[m_changeSceneQueue.front()]);
        m_changeSceneQueue.pop();
    }
}

void Engine::HandleEvent(const Event& e)
{
    auto level = std::static_pointer_cast<int>(e.GetData());

    std::cout << "Switching to level: " << *level + 1<< std::endl;
    
    if (world.Scenes.size() > *level)
    {
        if (m_pCurScene == nullptr)
            ChangeScene(world.Scenes[*level]);
        else
            m_changeSceneQueue.push(*level);
    }
}

void Engine::Update()
{
    serviceLocator->EngineServices.GetWindow().Update();
    serviceLocator->EngineServices.GetFrameRateController()->Update();

    m_pCurScene->Update();
}

void Engine::Draw()
{
    m_pCurScene->Draw();
}

void Engine::PostUpdate()
{
    m_pCurScene->LateUpdate();
    SceneLateUpdate();

    serviceLocator->EngineServices.GetWindow().SwapBuffers();
    serviceLocator->EngineServices.GetInputSystem()->PollEvents();
    if (serviceLocator->EngineServices.GetWindow().ShouldClose())
        m_isRunning = false;
    serviceLocator->EngineServices.GetFrameRateController()->LateUpdate();
}

void Engine::Quit()
{
    for (auto scene : world.Scenes)
        delete scene;
    world.Scenes.clear();
    serviceLocator->EngineServices.GetEventSystem()->Unsubscribe(EventType::SceneChangeEvent, m_sceneChangeEventId);
    exit(EXIT_SUCCESS);
}

bool Engine::IsRunning()
{
    return m_isRunning;
}

ServiceLocator* ServiceLocator::GetInstance()
{
    if (!instance) {
        instance = new ServiceLocator();
    }
    return instance;
}