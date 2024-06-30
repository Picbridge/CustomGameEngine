#include "pch.h"

AABB::AABB() : m_scale(glm::vec3(1.0f)), min(glm::vec3(FLT_MAX)), max(glm::vec3(FLT_MIN)), Shape(AABB_RECT)
{
}

void AABB::Update()
{
	min = m_min * m_scale;
	max = m_max * m_scale;
	//std::cout << min.x << std::endl;
	//std::cout << max.x << std::endl;
}

void AABB::Scale(glm::vec3 scale)
{
	m_scale = scale;
}

void AABB::CalculateBound(const VertexData* vert)
{
	auto vertices = vert->vertexBuffer;
	for (const auto& vertex : vertices)
	{
		// right
		m_max.x = std::max(max.x, vertex.x);
		// left
		m_min.x = std::min(min.x, vertex.x);

		// top
		m_max.y = std::max(max.y, vertex.y);
		// bottom
		m_min.y = std::min(min.y, vertex.y);

		// forward
		m_max.z = std::max(max.z, vertex.z);
		// back
		m_min.z = std::min(min.z, vertex.z);
	}
}
