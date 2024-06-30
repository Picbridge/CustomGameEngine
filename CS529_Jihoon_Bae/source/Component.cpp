/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Component.cpp>
Purpose: <Component function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/05/2023>
--------------------------------------------------------*/
#include "pch.h"

void Component::SetOwner(GameObject* owner)
{
	pOwner = owner;
}