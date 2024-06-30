/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <CollisionFunctions.h>
Purpose: <Set of functions processing the collision test.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
class CollisionFunctions2D
{
public:
	CollisionFunctions2D() {}
	~CollisionFunctions2D() {}

	static bool CheckCollisionAABBAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionAABBCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionAABBOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	
	static bool CheckCollisionCircleAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionCircleCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionCircleOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	
	static bool CheckCollisionOBBAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionOBBCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);
	static bool CheckCollisionOBBOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact);

private:
	static bool NoGapExistsInAxis(Shape* shape1, Shape* shape2);
	
};

