/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <OBB.h>
Purpose: <OBB bounding box definition.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
class OBB : public Shape
{
public:
	glm::vec4 topLeft, topRight, bottomLeft, bottomRight;

	OBB();
	~OBB() {}

	// @brief updates the obb based on object tranformation
	void Update();

	// @brief get scale from the transform and set it to calculate bound
	void Scale(glm::vec3 scale);

	// @brief calculates the initial bound using the vertex buffer
	// @param vert: data that stores vertex buffer and normal buffer
	void CalculateBound(const VertexData* vert);

	// @brief get position from the transform and set it to calculate bound
	void Position(glm::vec3 center);

	// @brief get rotation from the transform and set it to calculate bound
	void Direction(glm::vec3 eulerAngles);

	//@brief generates and assign the axis for separation
	void GenNormals();

	// @brief run the projection to the input axis
	// @param axis: axis to try projection
	std::pair<float, float> GenProjection(const glm::vec3 axis);
	//-------------------
	// getter functions
	glm::vec3 GetAxis(int i) { return separatingAxes[i]; }
	glm::vec3 GetScale() { return m_scale; }
	glm::mat4 GetDirection() { return m_direction; }
	//-------------------

private:
	glm::vec3 m_scale;
	glm::vec4 m_center;
	glm::mat4 m_direction;

	glm::vec3 m_minExtents;
	glm::vec3 m_maxExtents;
	std::array<glm::vec3, 2> separatingAxes;
};
