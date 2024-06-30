/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <EnemyBehavior.cpp>
Purpose: <Manage Enemy health and gen>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/08/2023>
--------------------------------------------------------*/
#include "pch.h"

EnemyBehavior::EnemyBehavior() : m_onCollisionCallback([this](const Event& e) { OnCollisionEnter(e); }),
m_cloneEventCallback([this](const Event& e) { OnClone(e); })
{
	m_collisionEventId = EventManager::GetInstance()->Subscribe(EventType::OnCollisionEnter, m_onCollisionCallback);
	m_cloneEventId = EventManager::GetInstance()->Subscribe(EventType::CloneEvent, m_cloneEventCallback
	);
	m_cooldown.SetDurationinSeconds(1);

	m_windowHalfSize = 1.5f; 
	m_radius = sqrt(2 * m_windowHalfSize * m_windowHalfSize);
	m_hits = 1;
}
EnemyBehavior::~EnemyBehavior()
{
	Shutdown();
}

void EnemyBehavior::Init()
{
	GetOwner()->GetTransform()->SetPosition(getRandomPosition());
	m_cooldown.Reset();
	m_name = GetOwner()->GetName();
}

void EnemyBehavior::Update()
{

}

void EnemyBehavior::Shutdown()
{
	EventManager::GetInstance()->Unsubscribe(EventType::OnCollisionEnter, m_collisionEventId);
	EventManager::GetInstance()->Unsubscribe(EventType::CloneEvent, m_cloneEventId);
}

void EnemyBehavior::OnCollisionEnter(const Event& e)
{
	if (!m_cooldown.IsTimeOver()) return;
	auto contact = std::static_pointer_cast<Contact>(e.GetData());

	auto selfBody = contact->bodies[0];
	auto targetBody = contact->bodies[1];
	auto target = GameObjectFactory::GetInstance()->GetBodyOwner(targetBody);
	if (!GetComponent<PhysicsComponent>()->IsBodyOwner(selfBody)) return;
	if (target == nullptr) return;
	if (target->parent && target->parent == GetOwner()) return;
	if (target->GetName() != "Sword" || !GetOwner()->IsClone()) return;
	m_hits--;
	if (m_hits == 0)
	{
		GetOwner()->Destroy();
	}

	m_cooldown.Reset();
}

void EnemyBehavior::OnClone(const Event& e)
{
	auto namePtr = std::static_pointer_cast<std::string>(e.GetData());
	auto owner = GetOwner();
	
	if (owner->GetName() == *namePtr)
		owner->Clone();
}

void EnemyBehavior::SetHits(int hits)
{
	m_hits = hits;
}

glm::vec3 EnemyBehavior::getRandomPosition()
{
	std::random_device rd;
	std::uniform_real_distribution<> distr(-m_radius, m_radius); 
	std::mt19937 eng(rd());

	glm::vec3 randomPoint;
	bool pointIsValid = false;

	while (!pointIsValid) {
		float x = (float)distr(eng);
		float y = (float)distr(eng);

		if (std::sqrt(x * x + y * y) <= m_radius) {
			if (std::abs(x) > m_windowHalfSize || std::abs(y) > m_windowHalfSize) {
				randomPoint = glm::vec3(x, y, 0);
				pointIsValid = true;
			}
		}
	}

	return randomPoint;
}
