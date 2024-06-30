/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <InputManager.cpp>
Purpose: <Responsible for initializing, and managing the input system.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/20/2023>
--------------------------------------------------------*/
#include "pch.h"

// set as singleton
InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	std::fill(isCurPressed.begin(), isCurPressed.end(), false);
	std::fill(isCurReleased.begin(), isCurReleased.end(), false);
	std::fill(isPrevPressed.begin(), isPrevPressed.end(), false);
	std::fill(isPrevReleased.begin(), isPrevReleased.end(), false);
}

InputManager* InputManager::GetInstance()
{
	if (!instance) {
		instance = new InputManager();
	}
	return instance;
}

InputManager::~InputManager()
{

}

void InputManager::Init()
{
	mapKeys();
	std::cout << "Input System Initialized" << std::endl;
}

void InputManager::PollEvents()
{
	glfwPollEvents();
	UpdateCurrentKeyStates();
}

bool InputManager::IsKeyUp(InputKeys key)
{
	return  !curKeyStates[(int)key];
}

bool InputManager::IsKeyDown(InputKeys key)
{
	return  curKeyStates[(int)key];
}

bool InputManager::IsKeyPressed(InputKeys key)
{
	int index = (int)key;
	return (isCurPressed[index] && !isPrevPressed[index]);
}

bool InputManager::IsKeyReleased(InputKeys key)
{
	int index = (int)key;
	return (!isCurPressed[index] && isPrevPressed[index]);
}

bool InputManager::IsKeyOnHold(InputKeys key)
{
	int index = (int)key;
	return (isCurPressed[index] && isPrevPressed[index]);
}

//Not used at this time
bool InputManager::IsLMouseDown(InputKeys key)
{
	return false;
}

bool InputManager::IsLMouseUp(InputKeys key)
{
	return false;
}
//---------------------


void InputManager::mapKeys()
{
	/*switch (glfwKey)
	{
	case GLFW_KEY_X: return InputKeys::X;
	case GLFW_KEY_Y: return InputKeys::Y;
	case GLFW_KEY_UP: return InputKeys::UP;
	case GLFW_KEY_DOWN: return InputKeys::DOWN;
	case GLFW_KEY_LEFT: return InputKeys::LEFT;
	case GLFW_KEY_RIGHT: return InputKeys::RIGHT;
	default: return InputKeys::MAX_KEYS;
	}*/

	m_keyMap[GLFW_KEY_X] = InputKeys::X;
	m_keyMap[GLFW_KEY_Y] = InputKeys::Y;
	m_keyMap[GLFW_KEY_UP] = InputKeys::UP;
	m_keyMap[GLFW_KEY_DOWN] = InputKeys::DOWN;
	m_keyMap[GLFW_KEY_LEFT] = InputKeys::LEFT;
	m_keyMap[GLFW_KEY_RIGHT] = InputKeys::RIGHT;
	m_keyMap[GLFW_KEY_LEFT_BRACKET] = InputKeys::LEFT_BRACKET;
	m_keyMap[GLFW_KEY_RIGHT_BRACKET] = InputKeys::RIGHT_BRACKET;
	m_keyMap[GLFW_KEY_SPACE] = InputKeys::SPACE;
	m_keyMap[GLFW_KEY_W] = InputKeys::W;
	m_keyMap[GLFW_KEY_A] = InputKeys::A;
	m_keyMap[GLFW_KEY_S] = InputKeys::S;
	m_keyMap[GLFW_KEY_D] = InputKeys::D;
}

KeyState InputManager::mapStates(int glfwKeyState)
{
	switch (glfwKeyState)
	{
	case GLFW_PRESS: return KeyState::PRESSED;
	case GLFW_RELEASE: return KeyState::RELEASED;
	default: return KeyState::MAX_STATES;

	}
}

void InputManager::UpdateCurrentKeyStates()
{
	GLFWwindow* pWindow = Renderer::GetInstance()->GetWindow();
	for (const auto& mapping : m_keyMap)
		curKeyStates[mapping.second] = glfwGetKey(pWindow, mapping.first);

	for (auto i = 0; i < InputKeys::MAX_KEYS; i++)
	{
		isPrevPressed[i] = isCurPressed[i];
		isPrevReleased[i] = isCurReleased[i];

		if (curKeyStates[i])
		{
			isCurPressed[i] = true;
			isCurReleased[i] = false;
		}
		else
		{
			isCurPressed[i] = false;
			isCurReleased[i] = true;
		}
	}
	

}

void InputManager::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
