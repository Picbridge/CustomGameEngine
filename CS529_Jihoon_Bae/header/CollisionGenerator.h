/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <CollisionGenerator.h>
Purpose: <Responsible for generating and storing collision events.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once

class Contact
{
public:
	Contact() : bodies({ nullptr, nullptr }) {}
	~Contact() {}

	std::array<Body*, 2> bodies;
};

typedef bool(*CollisionTest)
(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* constact);

class CollisionGenerator
{
public:
	CollisionGenerator() {}
	~CollisionGenerator() {}

	//-------------------
	// collision management

	// @brief assign test function between bodytype
	// @param bodyType1: first bodytype
	// @param bodyType2: second bodytype
	// @param fn: collision test function between two bodytypes
	// @return a normalized right vector
	void RegisterCollisionTests(PhysicsShapeType bodyType1, PhysicsShapeType bodyType2, CollisionTest fn);
	
	// @brief run test between two shapes
	// @param a: first shape
	// @param aPos: first body position
	// @param b: second shape
	// @param bPos: second body position
	// @param contact: only used when collided. Stores collided body info 
	// @return whether if there was collision between two types
	bool GenContacts(Shape* a, glm::vec3 aPos, Shape* b, glm::vec3 bPos, Contact* contact);

	// @brief removes all the stored contacts
	void ClearContacts();

	// @brief stores the collisioninfo
	// @param contact: collision info
	void RegisterContact(Contact* contact);
	//-------------------

	//-------------------
	// getter functions

	std::vector<Contact*>* GetContactReference() { return &m_contacts; }
	//-------------------

private:
	CollisionTest CollisionTable[MAX_SHAPES][MAX_SHAPES];
	std::vector<Contact*> m_contacts;
};

