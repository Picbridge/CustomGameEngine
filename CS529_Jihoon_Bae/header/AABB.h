/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <AABB.h>
Purpose: <AABB bounding box definition.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
class AABB : public Shape
{
public:
	glm::vec3 min, max;

	AABB();
	~AABB() {}

	// @brief updates the bounding box based on object tranformation
	void Update(); 

	// @brief get scale from the transform and set it to calculate bound
	void Scale(glm::vec3 scale);

	// @brief calculates the initial bound using the vertex buffer
	// @param vert: data that stores vertex buffer and normal buffer
	void CalculateBound(const VertexData* vert);

private:
	glm::vec3 m_scale;
	glm::vec3 m_min;
	glm::vec3 m_max;
};

