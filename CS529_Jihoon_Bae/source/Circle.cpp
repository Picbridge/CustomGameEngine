#include "pch.h"

Circle::Circle() : radius(0), m_radius(0),
					m_scale(glm::vec3(1)), m_center(glm::vec3(0)), 
					Shape(CIRCLE)
{
}

void Circle::Update()
{
	radius = m_radius * std::max(m_scale.x, m_scale.y);
}

void Circle::Scale(glm::vec3 scale)
{
	m_scale = scale;
}

void Circle::CalculateBound(const VertexData* vert)
{
	auto vertices = vert->vertexBuffer;
	for (const auto& vertex : vertices) 
		m_center += vertex;

	m_center /= vertices.size();

	float maxDistance = 0.0f;
	for (const auto& vertex : vertices) 
	{
		float distance = glm::length(vertex - m_center);
		maxDistance = std::max(maxDistance, distance);
	}

	m_radius = maxDistance;
}
