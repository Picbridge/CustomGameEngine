/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <SceneGraph.cpp>
Purpose: <SceneGraph to manage nodes>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/28/2023>
--------------------------------------------------------*/
#include "pch.h"

SceneGraph::SceneGraph() : m_nodeCount(0)
{

}

void SceneGraph::AddNode(Node* node)
{
    nodes.push_back(node);
    node->SetID(++m_nodeCount);
}

void SceneGraph::RemoveNode(Node* node)
{
    auto id = node->GetID();
    auto it = std::find_if(nodes.begin(), nodes.end(),
        [id](Node* node) { return node->GetID() == id; });

    // replace the last node with deleted one unless we are deleting the last node in order to prevent access violation
    if (it != nodes.end()) {
        auto lastNode = nodes.back();

        if (id != lastNode->GetID())
        {
            lastNode->SetID(id);
            *it = lastNode;
        }

        (*it)->Destroy();
        
        nodes.pop_back();
        m_nodeCount--;
    }
}