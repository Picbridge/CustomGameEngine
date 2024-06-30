/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <MyGameEngine.cpp>
Purpose: <The main application body>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_1>
Author: <jihoon.bae>
Creation date: <09/03/2023>
--------------------------------------------------------*/
#include "pch.h"



int main()
{
	Game game = *Game::GetInstance();

	game.Init();
	game.Run();
	game.Quit();
}