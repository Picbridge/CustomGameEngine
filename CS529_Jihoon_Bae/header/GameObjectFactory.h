/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <GameObjectFactory.h>
Purpose: <datadriven GameObject management>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/09/2023>
--------------------------------------------------------*/
#pragma once
class GameObjectFactory
{
public:
	static GameObjectFactory* GetInstance();

	// @brief creates game object with extracted components
	// @param member: set of component name and data 
	GameObject* CreateGameObject(rapidjson::Value::ConstMemberIterator member, std::string customName = "");

	// @brief load in the json and create game objects based on the data loaded
	// @param source: path of the json file 
	void CreateAllGameObjects(const char* source);

	// @brief initializes the created game objects 
	void InitializeGameObjects();

	// @brief search game object by name
	// @param name: name of the object
	GameObject* QuickFind(const char* name);

	void FlushDeletedGameObjects();

	void DeleteAllGameObjects();

	void AddToDelete(GameObject* go);

	void Update();

	void Draw();

	// @brief Returns the owner of the body
	// @param body: body to check ownership
		GameObject* GetBodyOwner(Body* body);
private:
	static GameObjectFactory* instance;

	std::unordered_map<std::string,GameObject*> m_gameObjectDictionary;
	std::vector<GameObject*> m_gameObjectsToDelete;
	GameObjectFactory() { }

};

