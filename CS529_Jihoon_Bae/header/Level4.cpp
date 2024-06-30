#include "pch.h"

Level4::Level4()
{
	gameObjectFile = "data/LoseData.json";
	sceneGraphFile = "";
	m_timer.SetDurationinSeconds(2);
}

Level4::~Level4()
{

}

void Level4::Init()
{
	Scene::Init();
	m_timer.Reset();
}


void Level4::Update()
{
	Scene::Update();
	if (m_timer.IsTimeOver())
	{
		auto title = std::make_shared<int>(LevelsConstants::TITLE);
		EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, title));
	}
}
