/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Behavior.cpp>
Purpose: <Events or behavior for specific GameObject>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/09/2023>
--------------------------------------------------------*/
#include "pch.h"

Behavior::Behavior() : m_onCollisionCallback([this](const Event& e) { OnCollisionEnter(e); })
{
	m_id = EventManager::GetInstance()->Subscribe(EventType::OnCollisionEnter, m_onCollisionCallback);
	m_cooldown.SetDurationinSeconds(2);
	m_playerHealth = 5;
}

Behavior::~Behavior()
{
	Shutdown();
}

void Behavior::Init()
{
	m_cooldown.Reset();
	genHealthObj();
}

void Behavior::Update()
{
}

void Behavior::Shutdown()
{
	EventManager::GetInstance()->Unsubscribe(EventType::OnCollisionEnter, m_id);
}

void Behavior::OnCollisionEnter(const Event& e)
{
	if (!m_cooldown.IsTimeOver()) return;

	if (GetComponent<PhysicsComponent>() == nullptr || GetComponent<PhysicsComponent>()->GetBody() == nullptr) return;
	auto contact = std::static_pointer_cast<Contact>(e.GetData());

	auto selfBody = contact->bodies[0];
	auto targetBody = contact->bodies[1];

	if (!GetComponent<PhysicsComponent>()->IsBodyOwner(selfBody)) return;

	auto target = GameObjectFactory::GetInstance()->GetBodyOwner(targetBody);
	if (target == nullptr) return;
	if (target->parent && target->parent == GetOwner()) return;

	m_playerHealth--;
	m_heartUI[m_heartUI.size() - 1]->Destroy();
	m_heartUI.pop_back();

	if (m_playerHealth == 0)
	{
		auto lose = std::make_shared<int>(LevelsConstants::LOSE);
		EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, lose));
	}
	m_cooldown.Reset();
}

void Behavior::genHealthObj()
{
    // Needs to be updated to current scene object data
    auto source = "data/PlayerHealthData.json";

	GameObjectFactory::GetInstance()->CreateAllGameObjects(source);

	source = "data/PlayerHealth_Hierarchy.json";

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

	const rapidjson::Value& rootObject = sceneGraphDoc.FindMember("Player")->value;

	recursiveProcessNewChildren(rootObject, static_cast<Node*>(GetOwner()));
	fclose(fp);
}

void Behavior::recursiveProcessNewChildren(const rapidjson::Value& nodeValue, Node* parentNode)
{
	for (auto it = nodeValue.MemberBegin(); it != nodeValue.MemberEnd(); ++it) {
		std::string gameObjectName = it->name.GetString();

		GameObject* gameObject = GameObjectFactory::GetInstance()->QuickFind(gameObjectName.c_str());
		if (gameObject == nullptr) {
			std::cerr << "GameObject with name '" << gameObjectName << "' not found!" << std::endl;
			continue;
		}
		m_heartUI.push_back(gameObject);
		parentNode->AddChild(gameObject);

		const rapidjson::Value& children = it->value;
		recursiveProcessNewChildren(children, gameObject);
	}
}