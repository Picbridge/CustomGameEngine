/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <CollisionGenerator.cpp>
Purpose: <Responsible for generating and storing collision events.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#include "pch.h"

void CollisionGenerator::RegisterCollisionTests(PhysicsShapeType bodyType1, PhysicsShapeType bodyType2, CollisionTest fn)
{
	CollisionTable[bodyType1][bodyType2] = fn;
}

bool CollisionGenerator::GenContacts(Shape* a, glm::vec3 aPos, Shape* b, glm::vec3 bPos, Contact* contact)
{
	return (*CollisionTable[a->GetType()][b->GetType()])(a, aPos, b, bPos, contact);
}

void CollisionGenerator::ClearContacts()
{
	for (auto contact : m_contacts)
		contact = nullptr;
	m_contacts.clear();
}

void CollisionGenerator::RegisterContact(Contact* contact)
{
	
	// Set the contact field in the event
	std::shared_ptr<Contact> contactPtr(contact);
	EventManager::GetInstance()->TriggerEvent(Event (EventType::OnCollisionEnter, contactPtr));
	m_contacts.push_back(contact);
}
