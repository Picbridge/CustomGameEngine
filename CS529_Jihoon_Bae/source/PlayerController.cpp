/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <PlayerController.cpp>
Purpose: <Game object controller>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/07/2023>
--------------------------------------------------------*/
#include "pch.h"

PlayerController::PlayerController() : m_speed(18.0f), m_curDir(CurDirection::RIGHT)
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::Init()
{
}

void PlayerController::Update()
{
	if (GetOwner()->NeedsDeletion()) return;

	ChangeDirection();
	Move();
}

void PlayerController::Shutdown()
{
}

void PlayerController::HandleEvent(const Event& e)
{

}

void PlayerController::ChangeDirection()
{
	InputManager* input = InputManager::GetInstance();
	if ((input->IsKeyPressed(InputKeys::RIGHT) && m_curDir == CurDirection::LEFT) ||
		(input->IsKeyPressed(InputKeys::LEFT) && m_curDir == CurDirection::RIGHT))
	{
		auto scale = GetOwner()->GetTransform()->GetScale() * glm::vec3(-1.0f, 1.0f, 1.0f);
		GetOwner()->GetTransform()->SetScale(scale);
	}
}

// object movement based on physics
//@param dt: delta time
void PlayerController::Move()
{
	auto body = GetComponent<PhysicsComponent>();
	if (body == nullptr) return;

	float dt = FrameRateController::GetInstance()->GetDT();

	InputManager* input = InputManager::GetInstance();
	auto position = GetComponent<TransformComponent>()->GetPosition();
	auto rotation = GetComponent<TransformComponent>()->GetRotation();
	auto vectorUp = VectorCalculation::GetUpVector(rotation) * m_speed * dt;
	//auto vectorForward = VectorCalculation::GetForwardVector(rotation);
	auto vectorRight = VectorCalculation::GetRightVector(rotation) * m_speed * dt;

	if ((input->IsKeyDown(InputKeys::UP) || input->IsKeyDown(InputKeys::W)) && position.y < 1.3)
	{
		body->SetForce(vectorUp);
	}
	else if ((input->IsKeyDown(InputKeys::DOWN) || input->IsKeyDown(InputKeys::S)) && position.y > -1.3)
	{
		body->SetForce(-vectorUp);
	}

	if ((input->IsKeyDown(InputKeys::RIGHT) || input->IsKeyDown(InputKeys::D)) && position.x < 1.3)
	{

		m_curDir = CurDirection::RIGHT;
		body->SetForce(vectorRight);
	}
	else if ((input->IsKeyDown(InputKeys::LEFT) || input->IsKeyDown(InputKeys::A)) && position.x > - 1.3)
	{

		m_curDir = CurDirection::LEFT;
		body->SetForce(-vectorRight);
	}
	body->Integrate();
}
