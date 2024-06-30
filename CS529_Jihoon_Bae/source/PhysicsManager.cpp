/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <PhysicsManager.cpp>
Purpose: <Responsible for generating phyicsbody for dynamics, and collision detection.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#include "pch.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager::PhysicsManager() : m_collisionGenerator(nullptr)
{
    m_gravity = glm::vec3(0.0f, -9.8f, 0.0f);
}

PhysicsManager* PhysicsManager::GetInstance()
{
    if (!instance) {
        instance = new PhysicsManager();
    }
    return instance;
}

// Initializes the collision test cases 
void PhysicsManager::Init()
{
   m_collisionGenerator = new CollisionGenerator();

   m_collisionGenerator->RegisterCollisionTests(AABB_RECT, AABB_RECT, CollisionFunctions2D::CheckCollisionAABBAABB);
   m_collisionGenerator->RegisterCollisionTests(AABB_RECT, CIRCLE, CollisionFunctions2D::CheckCollisionAABBCircle);
   m_collisionGenerator->RegisterCollisionTests(AABB_RECT, OBB_RECT, CollisionFunctions2D::CheckCollisionAABBOBB);

   m_collisionGenerator->RegisterCollisionTests(CIRCLE, AABB_RECT, CollisionFunctions2D::CheckCollisionCircleAABB);
   m_collisionGenerator->RegisterCollisionTests(CIRCLE, CIRCLE, CollisionFunctions2D::CheckCollisionCircleCircle);
   m_collisionGenerator->RegisterCollisionTests(CIRCLE, OBB_RECT, CollisionFunctions2D::CheckCollisionCircleOBB);

   m_collisionGenerator->RegisterCollisionTests(OBB_RECT, AABB_RECT, CollisionFunctions2D::CheckCollisionOBBAABB);
   m_collisionGenerator->RegisterCollisionTests(OBB_RECT, CIRCLE, CollisionFunctions2D::CheckCollisionOBBCircle);
   m_collisionGenerator->RegisterCollisionTests(OBB_RECT, OBB_RECT, CollisionFunctions2D::CheckCollisionOBBOBB);
}

Shape* PhysicsManager::DefineShape(PhysicsShapeType shape)
{
    try {
        switch (shape) {
        case CIRCLE:
            return new Circle();  // use smart pointers for memory management.
        case AABB_RECT:
            return new AABB();
        case OBB_RECT:
            return new OBB();
        default:
            throw std::invalid_argument("Unsupported shape type.");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error in DefineShape: " << ex.what() << std::endl;
        return nullptr;
    }
}

Body* PhysicsManager::BuildPhysicsBody()
{
    Body* body = new Body(static_cast<unsigned short>(m_physicsBodies.size()));
    body->Init();
    m_physicsBodies.push_back(body);

    return body;
}

Body* PhysicsManager::BuildPhysicsBody(PhysicsShapeType shape)
{
    Body* body = new Body(static_cast<unsigned short>(m_physicsBodies.size()));
    body->Init();
    m_physicsBodies.push_back(body);
    body->SetShape(DefineShape(shape));

    return body;
}

void PhysicsManager::DestroyPhysicsBody(Body* body)
{
    int delId = body->GetID();
    Body* lastBody = m_physicsBodies[m_physicsBodies.size() - 1];
    Body* delBody = m_physicsBodies[delId];

    // prevent self assign
    if (lastBody != delBody)
    {
        m_physicsBodies[delId] = lastBody;
        lastBody->SetID(delId);
    }
    m_physicsBodies.pop_back();

    delete delBody;
    delBody = nullptr;
}

void PhysicsManager::EvaluateCollisions()
{
    if (m_physicsBodies.size() < 2) return;
    for (Body* body1 : m_physicsBodies)
    {
        if (!body1 || !body1->GetShape())
            continue;

        for (Body* body2 : m_physicsBodies)
        {
            if (!body2 || !body2->GetShape())
                continue;

            if (body1 == body2)
                continue;

            body1->GetShape()->Update();
            body2->GetShape()->Update();
            Contact* contact = new Contact();

            if (m_collisionGenerator->GenContacts(body1->GetShape(), body1->GetPosition(), body2->GetShape(), body2->GetPosition(), contact))
            {
                contact->bodies[0] = body1;
                contact->bodies[1] = body2;
                m_collisionGenerator->RegisterContact(contact);
            }
        }
    }
}

void PhysicsManager::FlushCollisions()
{
    m_collisionGenerator->ClearContacts();
}

void PhysicsManager::SetGravity(float gravity)
{
    m_gravity = glm::vec3(0.0f, -gravity, 0.0f);
}