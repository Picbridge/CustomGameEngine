/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Geometry.cpp>
Purpose: <Geometry function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/22/2023>
--------------------------------------------------------*/
#include "pch.h"

Geometry::Geometry()
{
	glDisable(GL_DEBUG_OUTPUT);
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
}

Geometry::~Geometry() 
{
    // cleanup code
	glGenVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void Geometry::SetNormalBuffer(std::vector<glm::vec3> normalBuffer)
{
    m_vertexData.normalBuffer = normalBuffer;
}

void Geometry::SetVertexBuffer(std::vector<glm::vec3> vertexBuffer)
{
    m_vertexData.vertexBuffer = vertexBuffer;
}

void Geometry::SetupVertexAttributes(Material* material)
{
	GLint positionLocation = material->GetShader()->GetAttributeLocation("aPos");
	if (positionLocation != -1) {
		glEnableVertexAttribArray(positionLocation);
		glVertexAttribPointer(
			positionLocation, // attribute location
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);
	}

	GLint normalLocation = material->GetShader()->GetAttributeLocation("aNormal");
	if (normalLocation != -1) {
		glEnableVertexAttribArray(normalLocation);
		glVertexAttribPointer(
			normalLocation, // attribute location
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)(m_vertexData.normalBuffer.size() * sizeof(glm::vec3)) // array buffer offset
		);
	}
}

void Geometry::Bind()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	size_t dataSize = m_vertexData.vertexBuffer.size() * sizeof(glm::vec3) +
		m_vertexData.normalBuffer.size() * sizeof(glm::vec3);


	// Allocate memory for the combined data
	glBufferData(GL_ARRAY_BUFFER, dataSize, nullptr, GL_STATIC_DRAW);
	// Upload position data to the VBO
	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		m_vertexData.vertexBuffer.size() * sizeof(glm::vec3),
		m_vertexData.vertexBuffer.data());
	// Upload color data to the VBO
	glBufferSubData(GL_ARRAY_BUFFER,
		m_vertexData.vertexBuffer.size() * sizeof(glm::vec3),
		m_vertexData.normalBuffer.size() * sizeof(glm::vec3),
		m_vertexData.normalBuffer.data());
}

void Geometry::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
