/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Material.cpp>
Purpose: <Material function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/22/2023>
--------------------------------------------------------*/
#include "pch.h"

Material::Material() : m_pTextureDiffuse(nullptr), m_pTextureSpecular(nullptr)
{
	//Set shader as default shader
	m_pShader = Renderer::GetInstance()->GetShader("Default");
	m_materialData.color = glm::vec3(1.0f);
	m_materialData.shininess = 0.0f;
}

Material::Material(Shader* shader) : m_pTextureDiffuse(nullptr), m_pTextureSpecular(nullptr)
{
	//Set shader as default shader
	m_pShader = shader;
	m_materialData.color = glm::vec3(1.0f);
	m_materialData.shininess = 0.0f;
}

Material::~Material()
{
	//do not delete the shader
	if (m_pTextureDiffuse != nullptr)
	{
		delete m_pTextureDiffuse;
		m_pTextureDiffuse = nullptr;
	}
	if (m_pTextureSpecular != nullptr)
	{
		delete m_pTextureSpecular;
		m_pTextureDiffuse = nullptr;
	}
}

void Material::SetShader(Shader* shader)
{
	m_pShader = shader;
}


void Material::SetTextureDiffuse(const char* path)
{
	if (m_pTextureDiffuse != nullptr)
		delete m_pTextureDiffuse;

	m_pTextureDiffuse = new Texture(path);

	glm::vec3* dataDiff;

	m_pTextureDiffuse->getImage(dataDiff);
	glGenTextures(1, &m_materialData.diffuse);
	glBindTexture(GL_TEXTURE_2D, m_materialData.diffuse);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_pTextureDiffuse->getWidth(), m_pTextureDiffuse->getHeight(), 0, GL_RGB, GL_FLOAT, dataDiff);
	glGenerateMipmap(GL_TEXTURE_2D);
 }

void Material::SetTextureSpecular(const char* path)
{
	if (m_pTextureSpecular != nullptr)
		delete m_pTextureSpecular;

	m_pTextureSpecular = new Texture(path);

	glm::vec3* dataDiff;

	m_pTextureSpecular->getImage(dataDiff);
	glGenTextures(1, &m_materialData.specular);
	glBindTexture(GL_TEXTURE_2D, m_materialData.specular);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_pTextureSpecular->getWidth(), m_pTextureSpecular->getHeight(), 0, GL_RGB, GL_FLOAT, dataDiff);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Material::SetColor(glm::vec3 color)
{
	m_materialData.color = color / 255.0f;
}

void Material::SetColor(float r, float g, float b)
{
	m_materialData.color = glm::vec3(r, g, b) / 255.0f;
}

void Material::SetupUniformData()
{
	m_pShader->SetUniform("material.color", m_materialData.color);
	m_pShader->SetUniform("material.shininess", m_materialData.shininess);
	m_pShader->SetUniform("hasDiffuse", m_pTextureDiffuse != nullptr);
	m_pShader->SetUniform("hasSpecular", m_pTextureSpecular != nullptr);
}

void Material::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_materialData.diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_materialData.specular);
}

void Material::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}