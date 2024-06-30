/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <TransformComponent.h>
Purpose: <Transform component of the GameObject>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/07/2023>
--------------------------------------------------------*/
#pragma once
class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent() {}

	void Init();
	void Update();
	void Shutdown();
	void HandleEvent(const Event& e) override;


	// @brief sets the GameObject position
	// @param pos: new position of the GameObject
	void SetPosition(glm::vec3 pos);

	// @brief sets the GameObject rotation
	// @param pos: new rotation of the GameObject
	void SetRotation(glm::vec3 angle);

	// @brief sets the GameObject scale
	// @param pos: new scale of the GameObject
	void SetScale(glm::vec3 scale);

	// @brief sets the GameObject scale
	// @param pos: new scale of the GameObject
	void SetScale(float scale);

	//-------------------
	// getter functions

	glm::vec3 GetPosition() { return m_pTransform->GetPosition(); }
	glm::vec3 GetRotation() { return m_pTransform->GetRotation(); }
	glm::vec3 GetScale() { return m_pTransform->GetScale(); }

	glm::mat4 GetTranslationMatrix() { return m_pTransform->GetTranslationMatrix(); }
	glm::mat4 GetRotationMatrix() { return m_pTransform->GetRotationMatrix(); }
	glm::mat4 GetScaleMatrix() { return m_pTransform->GetScaleMatrix(); }
	glm::mat4 GetModelMatrix() { return m_pTransform->GetModel(); }
	//-------------------

private:
	Transform* m_pTransform;
};

