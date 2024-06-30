/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <GameObject.h>
Purpose: <A temporary sample game object for showcase>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/29/2023>
--------------------------------------------------------*/
#pragma once
class Component;
class GameObject : public Node
{
public:
	GameObject();
	~GameObject();

	void Update();
	
	// @brief deserialize the data extracted from json file
	// @param components: components information pulled out from json
	void Deserialize(const rapidjson::Value& components);

	// @brief set the current object name
	void SetName(std::string name);

	// @brief initialize all the components added
	void Init();

	void Draw();

	void SetDead(bool isDead);

	GameObject* Clone();

	template <typename DataType>
	typename std::enable_if_t<std::is_base_of<Component, DataType>::value, DataType*> AddComponent()
	{
		std::string dataType = Utils::GetClassName<DataType>();
		// assign new component
		m_components[dataType] = new DataType();
		setOwner(m_components[dataType]);
		initComponent(m_components[dataType]);
		return dynamic_cast<DataType*>(m_components[dataType]);
	}

	template <typename DataType>
	typename std::enable_if_t<std::is_base_of<Component, DataType>::value, void*> RemoveComponent()
	{
		std::string dataType = Utils::GetClassName<DataType>();

		auto del = m_components[dataType];
		m_components.erase(dataType);
		delete del;
		del = nullptr;
	}

    template <typename DataType>
    typename std::enable_if_t<std::is_base_of<Component, DataType>::value, DataType*> GetComponent()
    {
		std::string dataType = Utils::GetClassName<DataType>();
		// check if the current GameObject has the component of DataType
        if (m_components.find(dataType) != m_components.end())
            return dynamic_cast<DataType*>(m_components[dataType]);

		return nullptr;

    }
	
	std::string GetName() { return m_name; }
	bool IsDead() { return !m_isAlive; }
	bool IsClone() { return m_isClone; }
	void SetAsClone() { m_isClone = true; }
private:
	void setOwner(Component* sub);
	void initComponent(Component* sub);

	std::string m_name;
	std::unordered_map<std::string, Component*> m_components;
	bool m_isAlive;
	int m_numOfClones;
	bool m_isClone;
};

