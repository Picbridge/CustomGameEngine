
/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <GameResourceFactory.cpp>
Purpose: <datadriven game resource management>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/11/2023>
--------------------------------------------------------*/
#include "pch.h"

GameResourceFactory* GameResourceFactory::instance = nullptr;

GameResourceFactory* GameResourceFactory::GetInstance()
{
	if (!instance) {
		instance = new GameResourceFactory();
	}
	return instance;
}
void GameResourceFactory::StoreMaterials(rapidjson::Value::ConstMemberIterator member)
{;
	auto name = member->name.GetString();

	const rapidjson::Value& materialData = member->value;

	const char* diffuse = materialData[GameResourceConstants::DIFFUSE].GetString();

	if (materialData.HasMember(GameResourceConstants::SPECULAR))
	{
		const char* specular = materialData[GameResourceConstants::SPECULAR].GetString();
		Renderer::GetInstance()->AddMaterial(name, diffuse, specular);
	}
	else
		Renderer::GetInstance()->AddMaterial(name, diffuse);

	if (materialData.HasMember(GameResourceConstants::COLOR))
	{
		glm::vec3 color(materialData[GameResourceConstants::COLOR][0].GetFloat(),
			materialData[GameResourceConstants::COLOR][1].GetFloat(),
			materialData[GameResourceConstants::COLOR][2].GetFloat()
		);

		Renderer::GetInstance()->GetMaterial(name)->SetColor(color);
	}
	

}

void GameResourceFactory::StoreShaders(rapidjson::Value::ConstMemberIterator member)
{
	auto name = member->name.GetString();

	const rapidjson::Value& shaderData = member->value;

	const char* vert = shaderData[GameResourceConstants::VERTEX_SHADER].GetString();
	const char* frag = shaderData[GameResourceConstants::FRAGMENT_SHADER].GetString();
	if (shaderData.HasMember(GameResourceConstants::GEOMETRY_SHADER))
	{
		const char* geom = shaderData[GameResourceConstants::GEOMETRY_SHADER].GetString();
		Renderer::GetInstance()->AddShader(name, vert, frag, geom);
	}
	else
		Renderer::GetInstance()->AddShader(name, vert, frag);
}

void GameResourceFactory::StoreAllResources(const char* source)
{
	FILE* fp;
	fopen_s(&fp, source, "rb");
	if (!fp)
	{
		std::cout << "Failed to load data source" << std::endl;
		exit(EXIT_FAILURE);
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document resourceDoc;
	resourceDoc.ParseStream(inputStream);

	if (resourceDoc.HasMember("Materials"))
	{
		const rapidjson::Value& materials = resourceDoc.FindMember("Materials")->value;
		for (rapidjson::Value::ConstMemberIterator it = materials.MemberBegin(); it != materials.MemberEnd(); ++it)
			this->StoreMaterials(it);
	}
	
	if (resourceDoc.HasMember("Shaders"))
	{
		const rapidjson::Value& shaders = resourceDoc.FindMember("Shaders")->value;
		for (rapidjson::Value::ConstMemberIterator it = shaders.MemberBegin(); it != shaders.MemberEnd(); ++it)
			this->StoreShaders(it);
	}

	fclose(fp);
	std::cout << "Game Resource Loaded" << std::endl;
}