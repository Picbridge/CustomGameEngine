/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <VectorCalculation.h>
Purpose: <A set of functions for vector calculations>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/20/2023>
--------------------------------------------------------*/
#pragma once
#include <glm/vec3.hpp>

class VectorCalculation
{
public:
	// @brief returns the calculated up vector for given rotation
	// @param rotation: an Euler angle of a target
	// @return a normalized up vector
	static glm::vec3 GetUpVector(const glm::vec3 rotation);

	// @brief returns the calculated forward vector for given rotation
	// @param rotation: an Euler angle of a target
	// @return a normalized forward vector
	static glm::vec3 GetForwardVector(const glm::vec3 rotation);

	// @brief returns the calculated right vector for given rotation
	// @param rotation: an Euler angle of a target
	// @return a normalized right vector
	static glm::vec3 GetRightVector(const glm::vec3& rotation);

	// @brief returns the direction from lhs to rhs
	// @param lhs: position of start point
	// @param rhs: position of destination point
	// @return a normalized direction vector
	static glm::vec3 GetDirection(const glm::vec3& lhs, const glm::vec3& rhs);
private:
	VectorCalculation() {}
	~VectorCalculation() {}
};
