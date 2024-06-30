/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <GameObject.cpp>
Purpose: <A sample object for showcase>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/29/2023>
--------------------------------------------------------*/
#include "pch.h"

GameObject::GameObject() : m_isAlive(true), m_name(""), m_numOfClones(0), m_isClone(false)
{
}

GameObject::~GameObject()
{
    for (auto it = m_components.begin(); it != m_components.end();)
    {
        if (it->second != nullptr)
        {
            it->second->SetOwner(nullptr);
            delete it->second;
            it->second = nullptr;
        }
        it = m_components.erase(it);
    }
}

void GameObject::Update()
{
	for (auto component : m_components)
	{
		component.second->Update();
	}
}

void GameObject::Deserialize(const rapidjson::Value& components)
{
    for (auto& comp : components.GetObject())
    {
        std::string componentName = comp.name.GetString();

        // handle Transform component
        if (componentName == GameObjectSystemComponentConstants::TRANSFORM_COMPONENT)
        {
            auto transformComponent = AddComponent<TransformComponent>();

            const rapidjson::Value& transformData = comp.value;

            glm::vec3 position(transformData[GameObjectSystemComponentConstants::POSITION][0].GetFloat(),
                transformData[GameObjectSystemComponentConstants::POSITION][1].GetFloat(),
                transformData[GameObjectSystemComponentConstants::POSITION][2].GetFloat());
            glm::vec3 rotation(transformData[GameObjectSystemComponentConstants::ROTATION][0].GetFloat(),
                transformData[GameObjectSystemComponentConstants::ROTATION][1].GetFloat(),
                transformData[GameObjectSystemComponentConstants::ROTATION][2].GetFloat());
            glm::vec3 scale(transformData[GameObjectSystemComponentConstants::SCALE][0].GetFloat(),
                transformData[GameObjectSystemComponentConstants::SCALE][1].GetFloat(),
                transformData[GameObjectSystemComponentConstants::SCALE][2].GetFloat());

            transformComponent->SetPosition(position);
            transformComponent->SetRotation(rotation);
            transformComponent->SetScale(scale);
        }

        // handle Render component
        else if (componentName == GameObjectSystemComponentConstants::RENDER_COMPONENT)
        {
            auto renderComponent = AddComponent<RenderComponent>();

            const rapidjson::Value& renderData = comp.value;

            std::string material = renderData[GameObjectSystemComponentConstants::MATERIAL].GetString();
            std::string geometry = renderData[GameObjectSystemComponentConstants::GEOMETRY].GetString();
            std::string shader = renderData[GameObjectSystemComponentConstants::SHADER].GetString();
            renderComponent->SetMaterial(Renderer::GetInstance()->GetMaterial(material));
            renderComponent->SetGeometry(geometry);
            renderComponent->SetShader(Renderer::GetInstance()->GetShader(shader));
        }

        // handle Physics component
        else if (componentName == GameObjectSystemComponentConstants::PHYSICS_COMPONENT)
        {
            auto physicsComponent = AddComponent<PhysicsComponent>();

            const rapidjson::Value& physicsData = comp.value;

            std::string shapeType = physicsData[GameObjectSystemComponentConstants::SHAPE_TYPE].GetString();
            float mass = physicsData[GameObjectSystemComponentConstants::MASS].GetFloat();
            float inertia = physicsData[GameObjectSystemComponentConstants::INERTIA].GetFloat();
            float friction = physicsData[GameObjectSystemComponentConstants::FRICTION].GetFloat();

            physicsComponent->SetShape(shapeType);
            physicsComponent->SetMass(mass);
            physicsComponent->SetInertia(inertia);
            physicsComponent->SetFriction(friction);
        }

        // handle custom components... add component handing as component gets added
        else if (componentName == GameObjectSystemComponentConstants::PLAYER_CONTROLLER)
        {
            AddComponent<PlayerController>();
        }

        else if (componentName == GameObjectSystemComponentConstants::BEHAVIOR)
        {
            AddComponent<Behavior>();
        }

        else if (componentName == GameObjectSystemComponentConstants::FOLLOW)
        {
            AddComponent<Follow>();
        }

        else if (componentName == GameObjectSystemComponentConstants::WEAPON)
        {
            AddComponent<Weapon>();
        }
        else if (componentName == GameObjectSystemComponentConstants::ENEMYBEHAVIOR)
        {
            auto enemyComponent = AddComponent<EnemyBehavior>();
            const rapidjson::Value& enemyData = comp.value;
            if (enemyData.HasMember(GameObjectSystemComponentConstants::HITS))
            {
                int hits = enemyData[GameObjectSystemComponentConstants::HITS].GetInt();
                enemyComponent->SetHits(hits);
            }
        }
    }
}

void GameObject::SetName(std::string name)
{
    m_name = name;
}

void GameObject::Init()
{
    Renderer::GetInstance()->GetSceneGraph().AddNode(this);
}

void GameObject::Draw()
{
    auto renderComponent = GetComponent<RenderComponent>();

    if (renderComponent != nullptr)
    {
        //---------Need to update project matrix later on
        float ratio = WindowHandler::GetInstance().FrameBuffer.Width / (float)WindowHandler::GetInstance().FrameBuffer.Height;
        GetTransform()->SetProjection(glm::ortho(-ratio, ratio, -ratio, ratio, -ratio, ratio));
        renderComponent->Draw();
    }
}

void GameObject::SetDead(bool isDead)
{
    m_isAlive = !isDead;
}

GameObject* GameObject::Clone()
{
    if (m_isClone) return nullptr;
    
    // Needs to be updated to current scene object data
    auto source = "data/ObjectData.json";

    FILE* fp;
    fopen_s(&fp, source, "rb");
    if (!fp)
    {
       std::cout << "Failed to load data source: " << source << std::endl;
        exit(EXIT_FAILURE);
    }

    char readBuffer[8192];
    rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document gameObjectDoc;
    gameObjectDoc.ParseStream(inputStream);

    auto gameObjectsMember = gameObjectDoc.FindMember("GameObjects");
    if (gameObjectsMember != gameObjectDoc.MemberEnd()) 
    {
        const rapidjson::Value& gameObjects = gameObjectsMember->value;

        if (gameObjects.IsObject()) 
        {
            auto gameObjectIt = gameObjects.FindMember(m_name.c_str());
            if (gameObjectIt != gameObjects.MemberEnd()) 
            {
                m_numOfClones++;
                auto clone = GameObjectFactory::GetInstance()->CreateGameObject(gameObjectIt, m_name + '_' + std::to_string(m_numOfClones));
                clone->SetAsClone();
            }
            else 
                std::cerr << "GameObject '" << m_name << "' not found in " << source << std::endl;
        }
    }
    else 
        std::cerr << "'GameObject' not found in " << source << std::endl;

    return nullptr;
}

void GameObject::setOwner(Component* sub)
{
	sub->SetOwner(this);
}

void GameObject::initComponent(Component* sub)
{
	sub->Init();
}