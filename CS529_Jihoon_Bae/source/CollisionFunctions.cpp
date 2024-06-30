#include "pch.h"

bool CollisionFunctions2D::CheckCollisionAABBAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	AABB* aabb1 = static_cast<AABB*>(shape1);
	AABB* aabb2 = static_cast<AABB*>(shape2);

	glm::vec2 rect1Center = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 rect2Center = glm::vec2(posShape2.x, posShape2.y);

	float rect1Left = rect1Center.x + aabb1->min.x;
	float rect1Right = rect1Center.x + aabb1->max.x;
	float rect1Top = rect1Center.y + aabb1->max.y;
	float rect1Bottom = rect1Center.y + aabb1->min.y;

	float rect2Left = rect2Center.x + aabb2->min.x;
	float rect2Right = rect2Center.x + aabb2->max.x;
	float rect2Top = rect2Center.y + aabb2->max.y;
	float rect2Bottom = rect2Center.y + aabb2->min.y;

	if (rect1Left > rect2Right||
		rect1Right < rect2Left||
		rect1Top < rect2Bottom||
		rect1Bottom > rect2Top)
	{
		return false;
	}

	contact->bodies[0] = aabb1->body;
	contact->bodies[1] = aabb2->body;
	return true;
}

bool CollisionFunctions2D::CheckCollisionAABBCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	AABB* aabb = static_cast<AABB*>(shape1);
	Circle* circle = static_cast<Circle*>(shape2);

	glm::vec2 rectCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 circleCenter = glm::vec2(posShape2.x, posShape2.y);

	float closestX = glm::clamp(circleCenter.x, rectCenter.x + aabb->min.x, rectCenter.x + aabb->max.x);
	float closestY = glm::clamp(circleCenter.y, rectCenter.y + aabb->min.y, rectCenter.y + aabb->max.y);

	float distance = glm::distance(circleCenter, glm::vec2(closestX, closestY));

	// if the distance is less than the circle's radius, they intersect
	if (distance < circle->radius)
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = aabb->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::CheckCollisionAABBOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	AABB* aabb = static_cast<AABB*>(shape1);
	OBB* obb = static_cast<OBB*>(shape2);

	glm::mat2x2 rotMatrix = glm::mat2x2(obb->GetDirection());
	glm::vec2 aabbCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 obbCenter = glm::vec2(posShape2.x, posShape2.y);

	glm::vec2 delta = obbCenter - aabbCenter;
	delta = glm::transpose(rotMatrix) * delta;

	glm::vec3 obbHalfExtents = 0.5f * obb->GetScale();
	glm::vec3 aabbHalfExtents = 0.5f * (aabb->max - aabb->min);

	glm::mat2x2 absRotationMatrix;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			absRotationMatrix[i][j] = std::abs(obb->GetDirection()[i][j]);
		}
	}
	glm::vec2 obbExtents = obbHalfExtents * absRotationMatrix;

	glm::vec2 aabbMin = -aabbHalfExtents;
	glm::vec2 aabbMax = aabbHalfExtents;

	// check for collision in local space
	if (std::abs(delta.x) > obbHalfExtents.x + aabbHalfExtents.x) {
		return false;
	}
	if (std::abs(delta.y) > obbHalfExtents.y + aabbHalfExtents.y) {
		return false;
	}

	contact->bodies[0] = obb->body;
	contact->bodies[1] = aabb->body;
	return true;
	return false;
}

bool CollisionFunctions2D::CheckCollisionCircleAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	Circle* circle = static_cast<Circle*>(shape1);
	AABB* aabb = static_cast<AABB*>(shape2);

	glm::vec2 circleCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 rectCenter = glm::vec2(posShape2.x, posShape2.y);

	float closestX = glm::clamp(circleCenter.x, rectCenter.x + aabb->min.x, rectCenter.x + aabb->max.x);
	float closestY = glm::clamp(circleCenter.y, rectCenter.y + aabb->min.y, rectCenter.y + aabb->max.y);

	float distance = glm::distance(circleCenter, glm::vec2(closestX, closestY));

	// if the distance is less than the circle's radius, they intersect
	if (distance < circle->radius)
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = aabb->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::CheckCollisionCircleCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	Circle* circle1 = static_cast<Circle*>(shape1);
	Circle* circle2 = static_cast<Circle*>(shape2);

	float dist = glm::length(posShape1 - posShape2);

	if (dist < (circle1->radius + circle2->radius))
	{
		contact->bodies[0] = circle1->body;
		contact->bodies[1] = circle2->body;
		return true;

	}
	return false;
}

bool CollisionFunctions2D::CheckCollisionCircleOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	Circle* circle = static_cast<Circle*>(shape1);
	OBB* obb = static_cast<OBB*>(shape2);
	
	glm::vec2 circleCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 obbCenter = glm::vec2(posShape2.x, posShape2.y);

	glm::vec2 delta = circleCenter - obbCenter;
	glm::vec3 obbHalfExtents = 0.5f * obb->GetScale();

	glm::mat4 obbDirection = obb->GetDirection();
	glm::vec4 rotatedLocalPoint = glm::inverse(obbDirection) * glm::vec4(delta.x, delta.y, 0.0f, 1.0f);
	
	// check if the rotated point is inside the OBB's local space extents
	bool insideX = std::abs(rotatedLocalPoint.x) <= obbHalfExtents.x;
	bool insideY = std::abs(rotatedLocalPoint.y) <= obbHalfExtents.y;

	if (insideX && insideY) 
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = obb->body;
		return true;
	}

	glm::vec2 closestPoint;
	closestPoint.x = glm::clamp(rotatedLocalPoint.x, -obbHalfExtents.x, obbHalfExtents.x);
	closestPoint.y = glm::clamp(rotatedLocalPoint.y, -obbHalfExtents.y, obbHalfExtents.y);

	glm::vec4 rotatedClosestPoint(closestPoint.x, closestPoint.y, 0.0f, 1.0f);
	glm::vec2 worldClosestPoint = glm::vec2(obbDirection * rotatedClosestPoint + glm::vec4(obbCenter.x, obbCenter.y, 0.0f, 1.0f));

	float distance = glm::length(circleCenter - worldClosestPoint);

	//If the distance is less than the circle's radius, there's a collision
	if (distance < circle->radius) 
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = obb->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::CheckCollisionOBBAABB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	OBB* obb = static_cast<OBB*>(shape1);
	AABB* aabb = static_cast<AABB*>(shape2);

	glm::mat2x2 rotMatrix = glm::mat2x2(obb->GetDirection());
	glm::vec2 obbCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 aabbCenter = glm::vec2(posShape2.x, posShape2.y);

	glm::vec2 delta = obbCenter - aabbCenter;
	delta = glm::transpose(rotMatrix) * delta;

	glm::vec3 obbHalfExtents = 0.5f * obb->GetScale();
	glm::vec3 aabbHalfExtents = 0.5f * (aabb->max - aabb->min);

	glm::mat2x2 absRotationMatrix;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			absRotationMatrix[i][j] = std::abs(obb->GetDirection()[i][j]);
		}
	}
	glm::vec2 obbExtents = obbHalfExtents * absRotationMatrix;

	glm::vec2 aabbMin = -aabbHalfExtents;
	glm::vec2 aabbMax = aabbHalfExtents;

	// Check for collision in local space
	if (std::abs(delta.x) > obbHalfExtents.x + aabbHalfExtents.x) {
		return false;
	}
	if (std::abs(delta.y) > obbHalfExtents.y + aabbHalfExtents.y) {
		return false;
	}

	contact->bodies[0] = obb->body;
	contact->bodies[1] = aabb->body;
	return true;
}

bool CollisionFunctions2D::CheckCollisionOBBCircle(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	OBB* obb = static_cast<OBB*>(shape1);
	Circle* circle = static_cast<Circle*>(shape2);

	glm::vec2 obbCenter = glm::vec2(posShape1.x, posShape1.y);
	glm::vec2 circleCenter = glm::vec2(posShape2.x, posShape2.y);

	glm::vec2 delta = circleCenter - obbCenter;
	glm::vec3 obbHalfExtents = 0.5f * obb->GetScale();

	glm::mat4 obbDirection = obb->GetDirection();
	glm::vec4 rotatedLocalPoint = glm::inverse(obbDirection) * glm::vec4(delta.x, delta.y, 0.0f, 1.0f);

	// check if the rotated point is inside the OBB's local space extents
	bool insideX = std::abs(rotatedLocalPoint.x) <= obbHalfExtents.x;
	bool insideY = std::abs(rotatedLocalPoint.y) <= obbHalfExtents.y;

	if (insideX && insideY)
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = obb->body;
		return true;
	}

	glm::vec2 closestPoint;
	closestPoint.x = glm::clamp(rotatedLocalPoint.x, -obbHalfExtents.x, obbHalfExtents.x);
	closestPoint.y = glm::clamp(rotatedLocalPoint.y, -obbHalfExtents.y, obbHalfExtents.y);

	glm::vec4 rotatedClosestPoint(closestPoint.x, closestPoint.y, 0.0f, 1.0f);
	glm::vec2 worldClosestPoint = glm::vec2(obbDirection * rotatedClosestPoint + glm::vec4(obbCenter.x, obbCenter.y, 0.0f, 1.0f));

	float distance = glm::length(circleCenter - worldClosestPoint);

	//If the distance is less than the circle's radius, there's a collision
	if (distance < circle->radius)
	{
		contact->bodies[0] = circle->body;
		contact->bodies[1] = obb->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::CheckCollisionOBBOBB(Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contact)
{
	OBB* obb1 = static_cast<OBB*>(shape1);
	OBB* obb2 = static_cast<OBB*>(shape2);

	obb1->GenNormals();
	obb2->GenNormals();

	if (NoGapExistsInAxis(obb1, obb2) && NoGapExistsInAxis(obb2, obb1))
	{
		contact->bodies[0] = obb1->body;
		contact->bodies[1] = obb2->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::NoGapExistsInAxis(Shape* shape1, Shape* shape2)
{
	OBB* obb1 = static_cast<OBB*>(shape1);
	OBB* obb2 = static_cast<OBB*>(shape2);

	// iterate over all separating axes of both OBBs
	for (int i = 0; i < 2; i++)
	{
		glm::vec3 axis1 = obb1->GetAxis(i);
		glm::vec3 axis2 = obb2->GetAxis(i);

		std::pair<float, float> projection1 = obb1->GenProjection(axis1);
		std::pair<float, float> projection2 = obb2->GenProjection(axis1);

		if (projection1.second < projection2.first || projection2.second < projection1.first)
			return false;

		projection1 = obb1->GenProjection(axis2);
		projection2 = obb2->GenProjection(axis2);

		if (projection1.second < projection2.first || projection2.second < projection1.first)
			return false;
	}

	// no gap found on all axes, so no collision gap exists
	return true;
}