/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <VectorCalculation.cpp>
Purpose: <A set of functions for vector calculations>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/20/2023>
--------------------------------------------------------*/
#include "pch.h"

glm::vec3 VectorCalculation::GetUpVector(const glm::vec3 rotation)
{
	glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

	// create a rotation matrix based on Euler angles
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

	// calculate the new up vector by transforming the original up vector
	glm::vec4 newUp = glm::normalize(rotationMatrix * glm::vec4(upVec, 0.0f));
	glm::vec3 res = glm::vec3(newUp);

	return res;
}

glm::vec3 VectorCalculation::GetForwardVector(const glm::vec3 rotation)
{
	glm::vec3 forwardVec = glm::vec3(
		glm::cos(glm::radians(rotation.x)) * glm::sin(glm::radians(rotation.y)),
		glm::sin(glm::radians(-rotation.x)),
		glm::cos(glm::radians(rotation.x)) * glm::cos(glm::radians(rotation.y))
	);

	glm::vec3 res = glm::normalize(forwardVec);
	return res;
}

glm::vec3 VectorCalculation::GetRightVector(const glm::vec3& rotation)
{
	glm::mat3 xMat = {
		{1,0                             ,0                              },
		{0,glm::cos(glm::radians(rotation.x)),glm::sin(glm::radians(-rotation.x))},
		{0,glm::sin(glm::radians(rotation.x)),glm::cos(glm::radians(rotation.x)) }
	};

	glm::mat3 yMat = {
		{glm::cos(glm::radians(-rotation.y)),0,glm::sin(glm::radians(rotation.y)) },
		{0                                  ,1,0                                  },
		{glm::sin(glm::radians(-rotation.y)),0,glm::cos(glm::radians(-rotation.y))}
	};

	glm::mat3 zMat = {
		{glm::cos(glm::radians(rotation.z)),glm::sin(glm::radians(-rotation.z)),0},
		{glm::sin(glm::radians(rotation.z)),glm::cos(glm::radians(rotation.z)) ,0},
		{0                                 ,0                                  ,1}
	};

	glm::vec3 rightVec = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 res = yMat * xMat * zMat * rightVec;

	return glm::normalize(res);
}

glm::vec3 VectorCalculation::GetDirection(const glm::vec3& lhs, const glm::vec3& rhs)
{
	glm::vec3 dir = rhs - lhs;
	return glm::normalize(dir);
}