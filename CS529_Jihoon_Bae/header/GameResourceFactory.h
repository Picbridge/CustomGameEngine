
/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <GameResourceFactory.h>
Purpose: <datadriven game resource management>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/11/2023>
--------------------------------------------------------*/
#pragma once
class GameResourceFactory
{
public:
	static GameResourceFactory* GetInstance();

	// @brief creates material with extracted components and store it for use
	// @param member: set of material name and data 
	void StoreMaterials(rapidjson::Value::ConstMemberIterator member);

	// @brief creates shader with extracted components and store it for use
	// @param member: set of shader name and data 
	void StoreShaders(rapidjson::Value::ConstMemberIterator member);

	// @brief load in the json and store the resource based on the data loaded
	// @param source: path of the json file 
	void StoreAllResources(const char* source);

private:
	static GameResourceFactory* instance;
	GameResourceFactory() {}

};