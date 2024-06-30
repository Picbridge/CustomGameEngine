/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <SceneGraph.h>
Purpose: <SceneGraph to manage nodes>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/28/2023>
--------------------------------------------------------*/

class Node;
#pragma once
class SceneGraph
{
public: 
	std::vector<Node*> nodes;
	SceneGraph();


	//-------------------
	// node management

	// @brief adds node to the current scene
	// @param node: node to add
	void AddNode(Node* node);

	// @brief removes the node from the scene
	// @param node: node to remove
	void RemoveNode(Node* node);
	//-------------------

private:
	int m_nodeCount;
};

