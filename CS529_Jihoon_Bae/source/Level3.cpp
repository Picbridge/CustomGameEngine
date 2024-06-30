#include "pch.h"

Level3::Level3()
{
	gameObjectFile = "data/WinData.json";
	sceneGraphFile = "";
	m_timer.SetDurationinSeconds(2);
}

Level3::~Level3()
{

}

void Level3::Init()
{
	Scene::Init();
	m_timer.Reset();
}


void Level3::Update()
{
	Scene::Update();
	if (m_timer.IsTimeOver())
	{
		auto title = std::make_shared<int>(LevelsConstants::TITLE);
		EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, title));
	}
}
