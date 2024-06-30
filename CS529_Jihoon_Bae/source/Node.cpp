/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Node.cpp>
Purpose: <Node function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/21/2023>
--------------------------------------------------------*/
#include "pch.h"

Node::Node() : parent(nullptr), m_needsDeletion(false), m_ID(-1)
{
	m_pTransform = new Transform();
	GetWorldTransform();
}

Node::~Node()
{
	delete m_pTransform;

	// delete all the child nodes on deletion
	for (auto kv : children)
	{
		kv.second->Destroy();
		//Renderer::GetInstance()->GetSceneGraph().RemoveNode(kv.second);
	}
}

void Node::AddChild(Node* node)
{
	node->parent = this;
	children[node->GetID()] = (node);
	node->GetWorldTransform();
}

void Node::RemoveChild(Node* node)
{
	auto it = children.find(node->GetID());

	if (it != children.end())
	{
		node->parent = nullptr;
		children.erase(it);
	}
}

void Node::SetID(int id)
{
	m_ID = id;
}

void Node::Draw()
{

}

void Node::Destroy()
{
	m_needsDeletion = true;
}
