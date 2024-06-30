/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Component.h>
Purpose: <GameObject component base class>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/08/2023>
--------------------------------------------------------*/
#pragma once
//class GameObject;
class Component
{
public:
	//friend class GameObject;

	Component() : pOwner(nullptr) {}
	virtual ~Component() {}
	//-------------------
	//Component essentials

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

	virtual void HandleEvent(const Event& e) {}

	// @brief assign ownership to the component
	// @param owner: the GameObject to get attached to
	void SetOwner(GameObject* owner);
	//-------------------
	// getter functions

	GameObject* GetOwner() { return pOwner; }

	template <typename DataType>
	DataType* GetComponent() { return pOwner->GetComponent<DataType>(); }
	//-------------------

protected:
	GameObject* pOwner;
};

