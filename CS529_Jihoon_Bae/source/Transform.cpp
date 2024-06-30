/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Transform.cpp>
Purpose: <Transform function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/26/2023>
--------------------------------------------------------*/
#include "pch.h"

Transform::Transform() 
	: m_model(glm::mat4(1.0f)), 
	  m_projection(glm::mat4(1.0f)),
	  m_view(glm::mat4(1.0f)),
	  m_position(glm::vec3(0.0f)),
	  m_rotation(glm::vec3(0.0f)), 
	  m_scale(glm::vec3(1.0f)),
	  m_translationMatrix(glm::mat4(1.0f)),
	  m_rotationMatrix(glm::mat4(1.0f)),
	  m_scaleMatrix(glm::mat4(1.0f))
{
}

void Transform::SetPosition(const glm::vec3 newPos)
{
	m_position = newPos;
	UpdateModel();
}

void Transform::SetRotation(const glm::vec3 newRot)
{
	m_rotation = newRot;
	UpdateModel();
}

void Transform::SetScale(const glm::vec3 newScale)
{
	m_scale = newScale;
	UpdateModel();

}

void Transform::SetProjection(const glm::mat4 projection)
{
	m_projection = projection;
}

void Transform::SetView(const glm::mat4 view)
{
	m_view = view;
}

void Transform::UpdateModel()
{
	m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
	m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

	m_model = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}
