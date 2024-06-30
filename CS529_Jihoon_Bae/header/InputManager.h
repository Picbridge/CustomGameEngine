/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <InputManager.h>
Purpose: <Responsible for initializing, and managing the input system.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/20/2023>
--------------------------------------------------------*/
#pragma once

class InputManager
{
public:

	static InputManager* GetInstance();
	~InputManager();
	//-------------------

	// @brief initialize the input manager
	void Init();

	// @brief detect the key inputs and update the key states
	void PollEvents();

	// @brief returns a bool type of whether if the key is currently up
	// @param key: a target key to check
	// @return true if key is up, false otherwise
	bool IsKeyUp(InputKeys key);

	// @brief returns a bool type of whether if the key is currently down
	// @param key: a target key to check
	// @return true if key is down, false otherwise
	bool IsKeyDown(InputKeys key);

	// @brief returns a bool type of whether if the key is pressed
	// @param  key: a target key to check
	// @return true if key state has changed from up to down.
	bool IsKeyPressed(InputKeys key);

	// @brief returns a bool type of whether if the key is released
	// @param key: a target key to check
	// @return true if key state has changed from down to up.
	bool IsKeyReleased(InputKeys key);

	// @brief returns a bool type of whether if the key on hold
	// @param key: a target key to check
	// @return true if key has been down continuously.
	bool IsKeyOnHold(InputKeys key);

	//Not used at this time
	bool IsLMouseDown(InputKeys key);
	bool IsLMouseUp(InputKeys key);
	//-------------------
private:

	InputManager();
	static InputManager* instance;

	// @brief 1:1 key mapping for input detection
	void mapKeys();

	// @brief 1:1 state mapping
	static KeyState mapStates(int glfwKeyState);

	// @brief detects the input and updates the states
	void UpdateCurrentKeyStates();
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	std::array<bool, InputKeys::MAX_KEYS> curKeyStates = {};

	std::array<bool, InputKeys::MAX_KEYS> isCurPressed;
	std::array<bool, InputKeys::MAX_KEYS> isCurReleased;
	std::array<bool, InputKeys::MAX_KEYS> isPrevPressed;
	std::array<bool, InputKeys::MAX_KEYS> isPrevReleased;

	std::unordered_map<int, InputKeys> m_keyMap;

};

