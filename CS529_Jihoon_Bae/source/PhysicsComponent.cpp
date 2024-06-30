#include "pch.h"

PhysicsComponent::PhysicsComponent() : 
	m_pPhysicsBody(nullptr),
	m_pShape(nullptr)
{
}

PhysicsComponent::~PhysicsComponent()
{
	Shutdown();
}

void PhysicsComponent::Init()
{
	m_pPhysicsBody = PhysicsManager::GetInstance()->BuildPhysicsBody();
}

void PhysicsComponent::Update()
{
	if (GetOwner()->NeedsDeletion()) return;
	if (m_pPhysicsBody == nullptr) return;

	auto render = GetComponent<RenderComponent>();

	auto shape = m_pPhysicsBody->GetShape();
	//std::cout << shape << std::endl;
	m_pPhysicsBody->SetTransform(GetOwner()->GetTransform());
	if (render != nullptr && shape != nullptr)
		shape->CalculateBound(render->GetGeometry()->GetVertexData());
}

void PhysicsComponent::Shutdown()
{
	if (m_pPhysicsBody == nullptr) return;
	PhysicsManager::GetInstance()->DestroyPhysicsBody(m_pPhysicsBody);
	m_pPhysicsBody = nullptr;
	if (m_pShape != nullptr)
	{
		delete m_pShape;
		m_pShape = nullptr;
	}
}

void PhysicsComponent::SetForce(glm::vec3 force)
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->AddForce(force);
}

void PhysicsComponent::SetTorque(glm::vec3 torque)
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->AddTorque(torque);
}

void PhysicsComponent::SetMass(float mass)
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->SetMass(mass);
}

void PhysicsComponent::SetInertia(float inertia)
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->SetInertia(inertia);
}

void PhysicsComponent::SetFriction(float friction)
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->SetFriction(friction);
}

void PhysicsComponent::SetShape(const std::string& shapeName)
{
	if (m_pPhysicsBody == nullptr) return;

	if (shapeName == "AABB")
		SetShape<AABB>();
	else if (shapeName == "OBB")
		SetShape<OBB>();
	else if (shapeName == "Circle")
		SetShape<Circle>();
	// add on as shape gets added

}


void PhysicsComponent::Integrate()
{
	if (m_pPhysicsBody == nullptr) return;
	m_pPhysicsBody->Integrate();
}

bool PhysicsComponent::IsBodyOwner(Body* body)
{
	//if (m_pPhysicsBody != nullptr && m_pPhysicsBody == body) return true;

	//for (auto child : GetOwner()->children)
	//{
	//	auto casted = dynamic_cast<GameObject*>(child.second);
	//	if (casted)
	//	{
	//		auto physics = casted->GetComponent<PhysicsComponent>();
	//		if (physics)
	//		{
	//			if (physics->IsBodyOwner(body))
	//				return true;
	//		}

	//	}
	//}

	return (m_pPhysicsBody != nullptr && m_pPhysicsBody == body);
}