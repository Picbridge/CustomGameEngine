/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <EventManager.cpp>
Purpose: <Responsible for adding, removing event handlers and use the stored callback.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#include "pch.h"

EventManager* EventManager::instance = nullptr;

EventManager* EventManager::GetInstance()
{
    if (!instance) {
        instance = new EventManager();
    }
    return instance;
}

int EventManager::Subscribe(EventType eventType, const EventHandler& handler)
{
    int id = m_nextId++;
    m_subscribers.push_back({ eventType,std::make_pair(handler, id) });
    return id;
}

void EventManager::Unsubscribe(EventType eventType, const int id) 
{
    m_subscribers.erase(
        std::remove_if(m_subscribers.begin(), m_subscribers.end(),
            [eventType, id](const auto& entry) {
                return entry.first == eventType && entry.second.second == id;
            }),
        m_subscribers.end());
    // Debugging: Check that the event has been removed
#ifndef NDEBUG
    auto iter = std::find_if(m_subscribers.begin(), m_subscribers.end(),
        [eventType, id](const auto& entry) {
            return entry.first == eventType && entry.second.second == id;
        });
    assert(iter == m_subscribers.end() && "Unsubscribe failed to remove the event handler");
#endif
}

void EventManager::TriggerEvent(const Event& event) 
{
    for (const auto& handler : m_subscribers) 
    {
        if (handler.first == event.GetType())
            handler.second.first(event);
    }
}

void EventManager::Shutdown()
{
    m_subscribers.clear();
}