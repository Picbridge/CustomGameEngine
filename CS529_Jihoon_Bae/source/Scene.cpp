#include "pch.h"

void Scene::LoadAssets()
{

}

void Scene::LoadGameObjects()
{
	std::cout << "Load Game Object For: " << gameObjectFile << std::endl;
	if (gameObjectFile.length() < 1) 
	{
		std::cout << "No Game Object File Assigned!" << std::endl;
		return;
	}
	ObjectFactory->CreateAllGameObjects(gameObjectFile.c_str());
	std::cout << "Game Objects Loaded!" << std::endl;
}

void Scene::BuildHierarchy()
{
	std::cout << "Building Hierarchy For: " << sceneGraphFile << std::endl;
	if (sceneGraphFile.length() < 1)
	{
		std::cout << "No Hierarchy File Assigned!" << std::endl;
		return;
	}
	auto source = sceneGraphFile.c_str();

	FILE* fp;
	fopen_s(&fp, source, "rb");
	if (!fp)
	{
		std::cout << "Failed to load data source" << std::endl;
		exit(EXIT_FAILURE);
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document sceneGraphDoc;
	sceneGraphDoc.ParseStream(inputStream);

	const rapidjson::Value& rootObject = sceneGraphDoc.FindMember("Root")->value;
	root = new Root();
	recursiveProcessNewChildren(rootObject, static_cast<Node*>(root));

	fclose(fp);

	std::cout << "Hierarchy Built!" << std::endl;
}

void Scene::recursiveProcessNewChildren(const rapidjson::Value& nodeValue, Node* parentNode)
{
	for (auto it = nodeValue.MemberBegin(); it != nodeValue.MemberEnd(); ++it) {
		std::string gameObjectName = it->name.GetString();

		GameObject* gameObject = GetGameObjectByName(gameObjectName.c_str());
		if (gameObject == nullptr) {
			std::cerr << "GameObject with name '" << gameObjectName << "' not found!" << std::endl;
			continue;
		}

		parentNode->AddChild(gameObject);
		if (parentNode == root)
			std::cout << gameObject->GetName() << " Added to Root!" << std::endl;
		else
			std::cout << gameObject->GetName() << " Added to " << static_cast<GameObject*>(parentNode)->GetName() << std::endl;

		const rapidjson::Value& children = it->value;
		recursiveProcessNewChildren(children, gameObject);
	}
}

void Scene::UnloadAssets()
{
	ObjectFactory->DeleteAllGameObjects();
}

void Scene::Init()
{
	LoadAssets();
	LoadGameObjects();
	BuildHierarchy();
}

void Scene::Update()
{
	PhysicsManager::GetInstance()->EvaluateCollisions();
	ObjectFactory->Update();
	inputActivity();
	recursiveLevelUpdate(root);
}

void Scene::LateUpdate()
{
	PhysicsManager::GetInstance()->FlushCollisions();
	flushDeletedGameObjects();

}

void Scene::Draw()
{
	ObjectFactory->Draw();
}

void Scene::Destroy()
{
	UnloadAssets();
}

void Scene::Pause()
{

}

void Scene::Resume()
{

}

void Scene::flushDeletedGameObjects()
{
	ObjectFactory->FlushDeletedGameObjects();
}


void Scene::recursiveLevelUpdate(Node* node)
{
}

void Scene::inputActivity()
{
}

