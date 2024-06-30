/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Shape.h>
Purpose: <Shape base class for bounding definition.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once

enum PhysicsShapeType
{
	CIRCLE,
	AABB_RECT,
	OBB_RECT,

	MAX_SHAPES
};

class Shape
{
public:
	Body* body;

	Shape() : body(nullptr), type(PhysicsShapeType::MAX_SHAPES) {}
	Shape(PhysicsShapeType type) : body(nullptr) { this->type = type; }

	virtual ~Shape() {};
	virtual void Update() = 0;
	virtual void Scale(glm::vec3 scale) = 0;
	virtual void CalculateBound(const VertexData* vert) = 0;

	// @brief sets the current type
	// @param type: type of the shape
	void SetType(PhysicsShapeType type);
	//-------------------
	// getter functions

	PhysicsShapeType GetType() { return type; }
	//-------------------
private:

protected:
	PhysicsShapeType type;
};

