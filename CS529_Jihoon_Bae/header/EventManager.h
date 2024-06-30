/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <EventManager.h>
Purpose: <Responsible for adding, removing event handlers and use the stored callback.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_4>
Author: <jihoon.bae>
Creation date: <10/22/2023>
--------------------------------------------------------*/
#pragma once

using EventHandler = std::function<void(const Event&)>;

class EventManager
{
public:
    static EventManager* GetInstance();

	EventManager() : m_nextId(0)
    {
        std::cout << "Event System Initialized" << std::endl;
    }

    // @brief stores new defined event callback function to specific event type
    // @param eventType: type of the event where callback function will be triggered
    // @param handler: event callback
    int Subscribe(EventType eventType, const EventHandler& handler);

    // @brief remove the registered callback
    // @param eventType: type of the event where callback function will be triggered
    // @param handler: event callback to remove
    void Unsubscribe(EventType eventType, const int id);

    // @brief triggers the callback function on event occurence
    // @param event: Event type parameter that stores data necessary for handling the event
    void TriggerEvent(const Event& event);

    // @brief clears the stored events on shutdown
    void Shutdown();
private:
    static EventManager* instance;
    std::vector<std::pair<EventType, std::pair<EventHandler, int>>> m_subscribers;
    int m_nextId;
};

