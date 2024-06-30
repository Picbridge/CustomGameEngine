/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Weapon.h>
Purpose: <Player weapon behavior.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/07/2023>
--------------------------------------------------------*/
#pragma once
class Weapon : public Component
{
public:
	Weapon();
	~Weapon();

	void Init();
	void Update();
	void ApplyOrbit(float angle);
	void Shutdown();
	void HandleEvent(const Event& event);
private:
	int normalizeAngle(int angle);

	float m_orbitRadius;    // Distance from the parent object
	float m_angularVelocity; // Speed of the orbit (radians per second)
	float m_angle;
	bool m_attack;
	float m_currentTime;
};

