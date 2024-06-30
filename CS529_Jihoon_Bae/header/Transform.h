/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Transform.h>
Purpose: <Transform class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/26/2023>
--------------------------------------------------------*/
#pragma once
class Transform
{
public:
	Transform();
	~Transform() {}
	//-------------------
	// model transform

	// @brief translates the object to given position
	// @param newPos: new position to assign
	void SetPosition(const glm::vec3 newPos);

	// @brief rotates the object to given rotation
	// @param newRot: new rotation to assign
	void SetRotation(const glm::vec3 newRot);

	// @brief scale the object by given scale
	// @param newScale: new scale to assign
	void SetScale(const glm::vec3 newScale);
	//-------------------

	//-------------------
	// matrix settings for MVP calculation

	// @brief assign the given projection matrix
	// @param projection: calculated projection matrix
	void SetProjection(const glm::mat4 projection);

	// @brief assign the given view matrix(typically camera view matrix)
	// @param view: view matrix to assign
	void SetView(const glm::mat4 view);
	//-------------------

	//-------------------
	// getter functions
	const glm::vec3 GetPosition() { return m_position; }
	const glm::vec3 GetRotation() { return m_rotation; }
	const glm::vec3 GetScale() { return m_scale; }
	const glm::mat4 GetModel() { return m_model; }
	const glm::mat4 GetProjection() { return m_projection; }
	const glm::mat4 GetView() { return m_view; }
	const glm::mat4 GetTranslationMatrix() { return m_translationMatrix; }
	const glm::mat4 GetRotationMatrix() { return m_rotationMatrix; }
	const glm::mat4 GetScaleMatrix() { return m_scaleMatrix; }
	//-------------------
private:
	glm::mat4 m_model;
	glm::mat4 m_projection;
	glm::mat4 m_view;

	glm::mat4 m_translationMatrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	// @brief called whenever new transform takes place
	void UpdateModel();
};

