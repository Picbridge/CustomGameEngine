/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Event.h>
Purpose: <Event class used for event handling>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once
enum class EventType {
    OnCollisionEnter,
    SceneChangeEvent,
    CloneEvent,

    MaxEvent
};

class Event
{
public:
    

    Event() : m_type(EventType::MaxEvent), m_data(nullptr) {}
    Event(EventType type) : m_data(nullptr) { m_type = type; }
    Event(EventType type, std::shared_ptr<void> data) { m_type = type; m_data = data; }
    ~Event() {};

    //-------------------
    // getter functions

    EventType GetType() const { return m_type; }
    std::shared_ptr<void> GetData() const { return m_data; }
    //-------------------

private:
    EventType m_type;
    std::shared_ptr<void> m_data;

};

