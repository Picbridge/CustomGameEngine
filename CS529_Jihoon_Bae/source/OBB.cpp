#include "pch.h"

OBB::OBB() : m_minExtents(glm::vec3(FLT_MAX)), m_maxExtents(glm::vec3(FLT_MIN)), Shape(OBB_RECT),
             topLeft(glm::vec4(0)), topRight(glm::vec4(0)), bottomLeft(glm::vec4(0)), bottomRight(glm::vec4(0))
{
}

void OBB::Update() 
{
    // calculate the local positions of the corners
    glm::vec4 localTopLeft =  glm::vec4(-m_scale.x, m_scale.y, 0.0f, 1.0f);
    glm::vec4 localTopRight =  glm::vec4(m_scale.x, m_scale.y, 0.0f, 1.0f);
    glm::vec4 localBottomLeft =  glm::vec4(-m_scale.x, -m_scale.y, 0.0f, 1.0f);
    glm::vec4 localBottomRight =  glm::vec4(m_scale.x, -m_scale.y, 0.0f, 1.0f);

    // transform the local positions to world space
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_center)) * m_direction;

    topLeft = transform * localTopLeft;
    topRight = transform * localTopRight;
    bottomLeft = transform * localBottomLeft;
    bottomRight = transform * localBottomRight;
}

void OBB::CalculateBound(const VertexData* vert)
{
    glm::mat4 transformationMatrix(1.0f);

    // apply transform
    transformationMatrix = glm::scale(transformationMatrix, m_scale);
    transformationMatrix = m_direction * transformationMatrix;
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(m_center));

    // apply the transformation matrix to each vertex
    for (auto vertex : vert->vertexBuffer) {
        glm::vec4 transformedVertex = transformationMatrix * glm::vec4(vertex, 1.0f);

        // Update min and max extents based on the transformed vertex
        m_minExtents = glm::min(m_minExtents, glm::vec3(transformedVertex));
        m_maxExtents = glm::max(m_maxExtents, glm::vec3(transformedVertex));
    }

    topLeft =     glm::vec4(m_minExtents.x, m_maxExtents.y, m_minExtents.z, 1.0f);
    topRight =    glm::vec4(m_maxExtents.x, m_maxExtents.y, m_minExtents.z, 1.0f);
    bottomLeft =  glm::vec4(m_minExtents.x, m_minExtents.y, m_minExtents.z, 1.0f);
    bottomRight = glm::vec4(m_maxExtents.x, m_minExtents.y, m_minExtents.z, 1.0f);

    
}

void OBB::Scale(glm::vec3 scale)
{
	m_scale = scale;
}

void OBB::Position(glm::vec3 center)
{
    m_center = glm::vec4(center, 1.0f);
}

void OBB::Direction(glm::vec3 eulerAngles)
{
	m_direction = glm::eulerAngleXYZ(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

void OBB::GenNormals()
{
	glm::vec3 v;
	
	v = (topRight - topLeft);
	glm::vec3 normal1 = glm::vec3(-v.y, v.x, 0.0f);

	v = (topRight - bottomRight);
	glm::vec3 normal2 = glm::vec3(-v.y, v.x, 0.0f);

	separatingAxes[0] = normal1;
	separatingAxes[1] = normal2;

}

std::pair<float, float> OBB::GenProjection(const glm::vec3 axis)
{
    glm::vec3 vertices[4] = { topLeft, topRight, bottomLeft, bottomRight };
    float outMin = glm::dot(vertices[0], axis);
    float outMax = outMin;
    for (int i = 1; i < 4; i++)
    {
        float projection = glm::dot(vertices[i], axis);
        if (projection < outMin)
            outMin = projection;
        else if (projection > outMax)
            outMax = projection;
    }
    return { outMin, outMax };
}
