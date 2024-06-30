/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Weapon.cpp>
Purpose: <Player weapon behavior.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/07/2023>
--------------------------------------------------------*/
#include "pch.h"

Weapon::Weapon() : m_angle(90.0f), m_angularVelocity(4.5f), m_orbitRadius(0.3f), m_attack(true), m_currentTime(0.0f)
{

}

Weapon::~Weapon()
{

}


void Weapon::Init()
{
}

void Weapon::Update()
{
    if (!m_attack) return;

    float dt = FrameRateController::GetInstance()->GetDT();
    m_currentTime += dt * m_angularVelocity;
    float sineFactor = std::sin(m_currentTime);
    float angleDelta = sineFactor * glm::radians(360.0f);

	m_angle -= angleDelta * dt;
	float rotationAngleDegrees = normalizeAngle(glm::degrees(m_angle));

	ApplyOrbit(m_angle);
    auto body = GetComponent<PhysicsComponent>()->GetBody();
	if (abs(sineFactor) < 0.1)
		m_angle = glm::radians(90.0f);
}

void Weapon::ApplyOrbit(float angle)
{   
    if (!GetOwner()) return;
    auto parent = GetOwner()->parent;
    if (parent == nullptr) return;

    float rotationAngleDegrees = normalizeAngle(glm::degrees(m_angle)) + 90;
    auto parentPos = parent->GetTransform()->GetPosition();
    // Calculate new position
    float newX = parentPos.x + std::cos(m_angle) * m_orbitRadius;
    float newY = parentPos.y + std::sin(m_angle) * m_orbitRadius;

    auto transform = GetComponent<TransformComponent>();
    
    if (transform == nullptr) return;
    transform->SetPosition(glm::vec3(newX, newY, parentPos.z));
    transform->SetRotation(glm::vec3(0, 0, rotationAngleDegrees));
    
}

void Weapon::Shutdown()
{

}

void Weapon::HandleEvent(const Event& event)
{

}

int Weapon::normalizeAngle(int angle)
{
    angle %= 360;
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}