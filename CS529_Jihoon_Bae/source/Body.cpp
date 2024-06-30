/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Body.cpp>
Purpose: <Physics body used for collision detection, dynamic movements.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#include "pch.h"

Body::Body(unsigned short id)
{
	m_pBodyShape = nullptr;
	m_pTransform = nullptr;
	m_ID = id;
	m_force = glm::vec3(0.0f, 0.0f, 0.0f);
	m_torque = glm::vec3(0.0f, 0.0f, 0.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

	m_mass = 1.0f;
	m_momentOfInertia = 0.01f;
	m_friction = 3.0f;
}

Body::~Body()
{
	m_pBodyShape = nullptr;
	m_pTransform = nullptr;
}

void Body::Init()
{

}

void Body::Integrate()
{
	if (m_pTransform == nullptr) return;

	float dt = FrameRateController::GetInstance()->GetDT();
	m_force += PhysicsManager::GetInstance()->GetGravity() * m_mass;
	m_velocity += m_force / m_mass * dt;
	m_angularVelocity += m_torque / m_momentOfInertia * dt;
	auto position = m_pTransform->GetPosition() + m_velocity;
	auto rotation = m_pTransform->GetRotation() + m_angularVelocity;

	m_pTransform->SetPosition(position);
	m_pTransform->SetRotation(rotation);

	m_force = glm::vec3(0.0f, 0.0f, 0.0f);
	m_velocity /= m_friction;
	m_torque = glm::vec3(0.0f, 0.0f, 0.0f);
	m_angularVelocity /= m_friction;

	UpdateShape();
}

void Body::SetShape(Shape* shape)
{
	m_pBodyShape = shape;
}

void Body::SetID(unsigned short id)
{
	m_ID = id;
}

void Body::SetTransform(Transform* transform)
{
	if (transform == nullptr) return;
	m_pTransform = transform;
	
	UpdateShape();
}

void Body::UpdateShape()
{
	auto shape = GetShape();
	if (shape == nullptr || m_pTransform == nullptr) return;
	shape->Scale(m_pTransform->GetScale());
	if (shape->GetType() == PhysicsShapeType::OBB_RECT)
	{
		static_cast<OBB*>(shape)->Position(m_pTransform->GetPosition());
		static_cast<OBB*>(shape)->Direction(m_pTransform->GetRotation());
	}
}

void Body::AddForce(glm::vec3 force)
{
	m_force += force;
}

void Body::AddTorque(glm::vec3 torque)
{
	m_torque += torque;
}

void Body::SetMass(float mass)
{
	m_mass  = mass;
}

void Body::SetInertia(float inertia)
{
	m_momentOfInertia = inertia;
}

void Body::SetFriction(float friction)
{
	m_friction  = friction;
}