#include "pch.h"

void Root::Init()
{
	Renderer::GetInstance()->GetSceneGraph().AddNode(this);
}

void Root::loadPhysics()
{
}

void Root::UpdatePhysics()
{
}

void Root::Draw()
{
}

std::vector<GameObject*> Root::GetRoots()
{
	std::vector<GameObject*> rootChildren;

	//for (auto node : children)
	//	rootChildren.push_back(static_cast<GameObject*>(node.second));

	return rootChildren;
}