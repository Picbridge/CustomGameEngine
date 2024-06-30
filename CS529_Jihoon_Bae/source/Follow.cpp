/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Follow.cpp>
Purpose: <Follows the main character>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/06/2023>
--------------------------------------------------------*/
#include "pch.h"


Follow::Follow():m_speed(10.0f)
{

}

Follow::~Follow()
{

}

void Follow::Init()
{
}

void Follow::Update()
{
	if (GetOwner()->NeedsDeletion()) return;
	if (GetOwner()->IsClone())
		Move();
}

void Follow::Shutdown()
{
}

void Follow::HandleEvent(const Event& e)
{

}

// object movement based on physics
//@param dt: delta time
void Follow::Move()
{
	InputManager* input = InputManager::GetInstance();

	if (input->IsKeyReleased(InputKeys::X))
	{
		auto clone = GetOwner()->Clone();
	}

	auto body = GetComponent<PhysicsComponent>();
	if (body == nullptr) return;

	float dt = FrameRateController::GetInstance()->GetDT();

	auto player = GameObjectFactory::GetInstance()->QuickFind("Player");
	if (player == nullptr) return;

	auto position = GetComponent<TransformComponent>()->GetPosition();
	auto dir = VectorCalculation::GetDirection(position, player->GetTransform()->GetPosition());

	auto force = m_speed * dir * dt;
	body->SetForce(force);

	body->Integrate();
}
