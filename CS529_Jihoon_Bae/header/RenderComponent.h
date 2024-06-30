/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <RenderComponent.h>
Purpose: <Manages the render sources and draws the GameObject>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/07/2023>
--------------------------------------------------------*/
#pragma once
class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void Init();
	void Update();
	void Shutdown();
	void HandleEvent(const Event& e) override;

	void Draw();

	// @brief change the current material color
	// @param color: color in rgb format
	void SetColor(glm::vec3 color);

	// @brief replace the current material with new user defined material
	// @param material: user defined material
	void SetMaterial(Material* material);

	// @brief replace the current shader with new user defined shader
	// @param shader: user defined shader
	void SetShader(Shader* shader);

	//@brief manually sets geometry based on the input datatype
	template <class T>
	void SetGeometry()
	{
		//delete the previous geometry and set for use
		if (m_pGeometry != nullptr)
		{
			m_pGeometry->Unbind();
			delete m_pGeometry;
		}
		m_pGeometry = new T();
		m_pGeometry->Bind();
		m_pGeometry->SetupVertexAttributes(m_pMaterial);
		m_pGeometry->Unbind();
	}
	
	// @brief geometry setter overload to set geometry by class name
	// @param geometryName: name of the geometry class to set
	void SetGeometry(const std::string& geometryName);
	//-------------------
	// getter functions

	Geometry* GetGeometry() { return m_pGeometry; }
	Shader* GetShader() { return m_pMaterial->GetShader(); }
	//-------------------

private:
	Geometry* m_pGeometry;
	Material* m_pMaterial;
};

