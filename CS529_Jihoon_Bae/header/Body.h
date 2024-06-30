/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Body.h>
Purpose: <Physics body used for collision detection, dynamic movements.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
class Shape;

class Body
{
public:
	Body(unsigned short id);

	// @brief remove transform if it's internal
	~Body();
	//-------------------
	// update and manage interaction between classes
	
	// @brief body class initialize
	void Init();

	// @brief updates the physical activities
	void Integrate();

	// @brief assign user defined shape to the body
	// @param shape: shape to assign to the body
	void SetShape(Shape* shape);

	// @brief ID setting for body entity management
	// @param id: new id
	void SetID(unsigned short id);

	// @brief assign position, scale, and direction on applicable shapes
	// @param transform: game object transform
	void SetTransform(Transform* transform);

	// @brief updates the body so that it moves along with the assigned game object
	void UpdateShape();

	//-------------------

	//-------------------
	// physics props management

	// @brief assign force(default vec3(0.0f))
	// @param force: custom force
	void AddForce(glm::vec3 force);

	// @brief assign torque(default vec3(0.0f))
	// @param torque: custom torque
	void AddTorque(glm::vec3 torque);

	// @brief assign mass of the game object(default 1.0f)
	// @param mass: user defined mass
	void SetMass(float mass);

	// @brief assign moment of inertia. lower the value, larger the angular velocity (default 0.01f)
	// @param inertia: user defined inertia
	void SetInertia(float inertia);

	// @brief assign fiction to movement and rotation(default 3.0f)
	// @param friction: user defined friction
	void SetFriction(float friction);
	//---------------------

	//-------------------
	// getter functions

	Shape* GetShape() { return m_pBodyShape; }
	unsigned short GetID() { return m_ID; }
	glm::vec3 GetPosition() { return m_pTransform->GetPosition(); }
	glm::vec3 GetRotation() { return m_pTransform->GetRotation(); }
	float GetMass() { return m_mass; }
	float GetInertia() { return m_momentOfInertia; }
	float GetFriction() { return m_friction; }
	//-------------------
private:
	Shape* m_pBodyShape;
	Transform* m_pTransform;
	glm::vec3 m_force, m_torque, m_velocity, m_angularVelocity;

	unsigned short m_ID;
	float m_mass;
	float m_momentOfInertia;
	float m_friction;
};

