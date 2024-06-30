/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Node.h>
Purpose: <Node class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/21/2023>
--------------------------------------------------------*/
#include "Geometry.h"
#include "Material.h"
#include "Transform.h"
#include <unordered_map>

#pragma once
class Node
{
public:
	Node* parent;
	std::unordered_map<int, Node*> children;

	Node();
	virtual ~Node();

	//-------------------
	// property control


	// @brief add a child node to current node
	// @param node: child node pointer
	virtual void AddChild(Node* node);

	// @brief removes the selected node from the current node children
	// @param node: child node to remove from the map
	virtual void RemoveChild(Node* node);

	// @brief sets the node ID (not for user)
	// @param id: id for the current node
	virtual void SetID(int id);

	virtual void Draw();

	virtual void Destroy();

	//-------------------

	//-------------------
	// getter functions

	virtual int GetID() { return m_ID; }
	virtual Transform*  GetTransform() { return m_pTransform; }
	virtual glm::mat4 GetWorldTransform() 
	{
		glm::mat4 parentTransform = (parent == nullptr) ? glm::mat4(1.0f) : parent->GetWorldTransform();
		m_worldTransform = m_pTransform->GetModel();
		return m_worldTransform;
	}
	//-------------------

	virtual bool NeedsDeletion() { return m_needsDeletion; }


protected:
	Transform* m_pTransform;
	glm::mat4 m_worldTransform;

	//ID for node entity control
	int m_ID;

	bool m_needsDeletion;
};

