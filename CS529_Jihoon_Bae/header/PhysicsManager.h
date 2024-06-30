/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <PhysicsManager.h>
Purpose: <Responsible for generating phyicsbody for dynamics, and collision detection.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
class PhysicsManager
{
public:
	static PhysicsManager* GetInstance();

	void Init();

	//-------------------
	// physics body control


	// @brief returns the mapped shape class
	// @param shape: type of the shape
	// @return actual shape of the input type
	Shape* DefineShape(PhysicsShapeType shape);

	// @brief generates new physics body and store it to manage
	// @return a generated body
	Body* BuildPhysicsBody();

	// @brief generates new physics body with shape assigned
	// @param shape: type of the shape
	// @return shape assigned body
	Body* BuildPhysicsBody(PhysicsShapeType shape);

	// @brief destroyes the input body and replace the destroyed ID with the last element
	// @param body: body to destroy
	void DestroyPhysicsBody(Body* body);

	// @brief runs through the test functions set in Init() and detect collision
	void EvaluateCollisions();

	// @brief clear out all the contacts stored
	void FlushCollisions();
	//-------------------

	// @brief sets world gravity (default 9.8f)
	// @param gravity: custom gravity
	void SetGravity(float gravity);
	
	//-------------------
	// getter functions

	glm::vec3 GetGravity() { return m_gravity; }
	//-------------------

private:
	static PhysicsManager* instance;
	CollisionGenerator* m_collisionGenerator;
	std::vector<Body*> m_physicsBodies;
	glm::vec3 m_gravity;

	PhysicsManager();
};

