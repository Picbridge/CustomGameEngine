#include "pch.h"

Game* Game::instance = nullptr;

Game* Game::GetInstance()
{
    if (!instance) {
        instance = new Game();
    }
    return instance;
}

Game::Game() : m_pEngine (Engine::GetInstance()), m_curLevel(0), MAX_LEVEL(0)
{
    std::cout << "Game Constructed" << std::endl;
}

void Game::Init()
{
    m_pEngine->Init();

    AddLevel<Level1>();//Title
    AddLevel<Level2>();//Level
    AddLevel<Level3>();//Win
    AddLevel<Level4>();//Lose

    auto titleLevel = std::make_shared<int>(LevelsConstants::TITLE);
    EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, titleLevel));
}

void Game::Run()
{
    
    while (m_pEngine->IsRunning())
    {
        InputManager* input = InputManager::GetInstance();
        if (input->IsKeyReleased(InputKeys::LEFT_BRACKET))
        {
            m_curLevel = m_curLevel <= 0 ? 0 : m_curLevel - 1;
            auto level = std::make_shared<int>(m_curLevel);
            EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, level));
        }
        else if (input->IsKeyReleased(InputKeys::RIGHT_BRACKET))
        {
            m_curLevel = m_curLevel >= MAX_LEVEL - 1 ? MAX_LEVEL - 1 : m_curLevel + 1;
            auto level = std::make_shared<int>(m_curLevel);
            EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, level));
        }

        m_pEngine->Update();
        m_pEngine->Draw(); 
        m_pEngine->PostUpdate();
    }
}

void Game::Reset()
{

}

void Game::Quit()
{
    std::cout << "Game Closed" << std::endl;
    m_pEngine->Quit();
}
