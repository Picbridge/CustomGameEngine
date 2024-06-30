/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <TriangleMesh.cpp>
Purpose: <Pre-defined mesh for triangle>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/24/2023>
--------------------------------------------------------*/
#include "pch.h"

TriangleMesh::TriangleMesh()
{
	m_vertexData.vertexBuffer = { 
		glm::vec3(-0.5f, -0.5f, 0.0f), 
		glm::vec3(0.0f, 0.5f, 0.0f), 
		glm::vec3(0.5f, -0.5f, 0.0f) 
	};

	m_vertexData.normalBuffer = {// not in use
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
}
