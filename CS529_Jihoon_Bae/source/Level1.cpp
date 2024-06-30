#include "pch.h"

Level1::Level1()
{
	gameObjectFile = "data/TitleData.json";
	sceneGraphFile = "";
}

Level1::~Level1()
{

}

void Level1::Update()
{
	if (InputManager::GetInstance()->IsKeyPressed(InputKeys::SPACE))
	{
		auto level = std::make_shared<int>(LevelsConstants::LEVEL_1);
		EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, level));
	}
}

