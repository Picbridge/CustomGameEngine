/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <PhysicsComponent.h>
Purpose: <Physics component derived from Component>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/08/2023>
--------------------------------------------------------*/
#pragma once
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void Init();
	void Update();
	void Shutdown();

	// @brief set or modify the force of the body
	// @param force: new force to set 
	void SetForce(glm::vec3 force);

	// @brief set or modify the torque of the body
	// @param vel: new torque to set 
	void SetTorque(glm::vec3 torque);

	// @brief set or modify the mass of the body
	// @param mass: new mass that will affect the force
	void SetMass(float mass);

	// @brief set or modify the inertia of the body
	// @param inertia: new mass that will affect the torque
	void SetInertia(float inertia);

	// @brief set or modify the friction of the body
	// @param friction: new friction that will affect the movement
	void SetFriction(float friction);
	
	// @brief set shape of the body
	template <class DataType>
	typename std::enable_if_t<std::is_base_of<Shape, DataType>::value, void> SetShape()
	{
		if (m_pPhysicsBody == nullptr || GetOwner() == nullptr) return;
		m_pShape = new DataType;
		m_pPhysicsBody->SetShape(m_pShape);
		auto render = GetComponent<RenderComponent>();

		m_pPhysicsBody->SetTransform(GetOwner()->GetTransform());
		if (render != nullptr)
			m_pShape->CalculateBound(render->GetGeometry()->GetVertexData());
	}

	// @brief shape of the body by class name
	// @param shapeName: name of the shape class to set
	void SetShape(const std::string& shapeName);

	// @brief integrate the settings to body
	void Integrate();

	// @brief Check if the body belongs to this game object
	// @param body: body to check ownership
	bool IsBodyOwner(Body* body);

	Body* GetBody() { return m_pPhysicsBody; }
private:
	Shape* m_pShape;
	Body* m_pPhysicsBody;
};

