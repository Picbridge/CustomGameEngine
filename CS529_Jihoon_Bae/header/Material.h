/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Material.h>
Purpose: <Material class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/22/2023>
--------------------------------------------------------*/
class Shader;
class Texture;

// define the dataset used in the shader program
struct MaterialData
{
	glm::vec3 color;
	GLuint diffuse;
	GLuint specular;
	float shininess;

};
#pragma once
class Material
{
public:
	Material();
	Material(Shader* shader);
	~Material();

	//-------------------
	// setting the current material

	// @brief replace the current shader with user defined shader
	// @param shader: user defined shader
	void SetShader(Shader* shader);

	// @brief apply the diffuse texture to current material
	// @param path: path and name for the diffuse texture
	void SetTextureDiffuse(const char* path);

	// @brief apply the specular texture to current material
	// @param path: path and name for the specular texture
	void SetTextureSpecular(const char* path);

	// @brief sets the color of the current material
	// @param color: color of range [0, 255]
	void SetColor(glm::vec3 color);

	// @brief sets the color of the current material
	// @param r: color of range [0, 255]
	// @param g: color of range [0, 255]
	// @param b: color of range [0, 255]
	void SetColor(float r, float g, float b);
	//-------------------

	//-------------------
	// rendering properties

	// @brief passes the material data to the shader
	void SetupUniformData();

	// @brief binds the texture set before
	void Bind();

	// @brief unbind the current texture for next object render
	void Unbind();
	//-------------------

	//-------------------
	// getter function

	Shader* GetShader() { return m_pShader; }
	//-------------------
private:
	Shader* m_pShader;
	Texture* m_pTextureDiffuse;
	Texture* m_pTextureSpecular;
	MaterialData m_materialData;
};

