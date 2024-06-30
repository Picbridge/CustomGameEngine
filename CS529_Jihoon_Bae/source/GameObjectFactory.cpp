#include "pch.h"
GameObjectFactory* GameObjectFactory::instance = nullptr;

GameObjectFactory* GameObjectFactory::GetInstance()
{
	if (!instance) {
		instance = new GameObjectFactory();
	}
	return instance;
}

GameObject* GameObjectFactory::CreateGameObject(rapidjson::Value::ConstMemberIterator member, std::string customName)
{
    GameObject* gameObject = new GameObject();
	if (customName.size() == 0)
		gameObject->SetName(member->name.GetString());
	else
		gameObject->SetName(customName);

    // iterate through the components of the game object
    const rapidjson::Value& components = member->value["Components"];
	gameObject->Deserialize(components);

	m_gameObjectDictionary[gameObject->GetName()] = gameObject;
    return gameObject;
}

void GameObjectFactory::CreateAllGameObjects(const char* source)
{
	FILE* fp;
	fopen_s(&fp, source, "rb");
	if (!fp)
	{
		std::cout << "Failed to load data source" << std::endl;
		exit(EXIT_FAILURE);
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document gameObjectDoc;
	gameObjectDoc.ParseStream(inputStream);

	const rapidjson::Value& gameObjects = gameObjectDoc.FindMember("GameObjects")->value;
	for (rapidjson::Value::ConstMemberIterator it = gameObjects.MemberBegin(); it != gameObjects.MemberEnd(); ++it)
		this->CreateGameObject(it);

	fclose(fp);
}
void GameObjectFactory::InitializeGameObjects()
{
	for (auto go : m_gameObjectDictionary)
		go.second->Init();
}

GameObject* GameObjectFactory::QuickFind(const char* name)
{
	return m_gameObjectDictionary[name];
}

void GameObjectFactory::FlushDeletedGameObjects()
{
	for (auto it = m_gameObjectDictionary.begin(); it != m_gameObjectDictionary.end();)
	{
		if (it->second != nullptr && it->second->NeedsDeletion())
		{
			delete it->second;
			it = m_gameObjectDictionary.erase(it);
		}
		else
			++it;
	}
}

void GameObjectFactory::DeleteAllGameObjects()
{
	for (auto go : m_gameObjectDictionary)
	{
		Renderer::GetInstance()->GetSceneGraph().RemoveNode(go.second);
		//go.second->Destroy();
	}

	m_gameObjectDictionary.clear();
}

void GameObjectFactory::AddToDelete(GameObject* go)
{
	m_gameObjectsToDelete.push_back(go);
}

void GameObjectFactory::Update()
{
	for (auto go : m_gameObjectDictionary)
		go.second->Update();
}

void GameObjectFactory::Draw()
{
	for (auto go : m_gameObjectDictionary)
		go.second->Draw();
}

GameObject* GameObjectFactory::GetBodyOwner(Body* body)
{
	for (auto go : m_gameObjectDictionary)
	{
		auto physics = go.second->GetComponent<PhysicsComponent>();
		if (physics && physics->IsBodyOwner(body))
		{
			return go.second;
		}
	}

	return nullptr;
}