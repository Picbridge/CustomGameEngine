/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <TransformComponent.h>
Purpose: <Physics component derived from Component>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/08/2023>
--------------------------------------------------------*/
#include "pch.h"

TransformComponent::TransformComponent():m_pTransform(nullptr)
{

}

void TransformComponent::Init()
{
	m_pTransform = GetOwner()->GetTransform();
}

void TransformComponent::Update()
{
	if (GetOwner()->NeedsDeletion()) return;
}

void TransformComponent::Shutdown()
{

}

void TransformComponent::HandleEvent(const Event& e)
{

}

void TransformComponent::SetPosition(glm::vec3 pos)
{
	m_pTransform->SetPosition(pos);
}

void TransformComponent::SetRotation(glm::vec3 angle)
{
	m_pTransform->SetRotation(angle);
}

void TransformComponent::SetScale(glm::vec3 scale)
{
	m_pTransform->SetScale(scale);
}

void TransformComponent::SetScale(float scale)
{
	m_pTransform->SetScale(glm::vec3(scale));
}
