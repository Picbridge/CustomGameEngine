/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Behavior.h>
Purpose: <Events or behavior for specific GameObject>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/09/2023>
--------------------------------------------------------*/
#pragma once
class Behavior : public Component
{
public:
	Behavior();
	~Behavior();

	void Init();

	void Update();

	void Shutdown();

	// @brief callback function on collision enter
	// @param e: Event containing contact information
	void OnCollisionEnter(const Event& e);

private:
	void genHealthObj();
	void recursiveProcessNewChildren(const rapidjson::Value& nodeValue, Node* parentNode);

	EventHandler m_onCollisionCallback;
	Timer m_cooldown;
	int m_id;
	int m_playerHealth;
	std::vector<GameObject*> m_heartUI;
};

