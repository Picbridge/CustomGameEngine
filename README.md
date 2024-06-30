# Custom 2D Game Engine project
---

Used OpenGL for rendering pipeline 

Implemented features:

- Renderer 2D
- Physics 2D
- Input System
- Event System
- GameObject Factory

## Building a new game:

The sample game script is included. Users can refer to **Game.cpp**.
Levels should be added on initializing step of game. 
Levels can be added by 
![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/9bf0159c-6a4e-4869-8862-29333be51336)
Where Level1 is a class name of the level.

Levels can be shifted by initializing the level id to **LevelConstants.h** file.

## Placing the object into the game scene:

The game object data should be defined per level.

Sample levels can be found in the build.

Data should be in json file format and should be placed in **data** folder.

For modifying the hierarchy of the object in the level, users can assign the json file that defines the hierarchy to the sceneGraphFile variable inside the level. 

The sample hierarchy looks like this:

![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/c9ba1932-cc9d-4600-bd46-c5f511593f35)


## Adding new resources:

New resources can be added in **ResourceData.json** in **data** folder.

It loads in the png file

![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/cbc1788b-8e55-4f45-8a95-4f5cdfad0357)

## Adding new components:

New components should be declared in following files
- GameObjectSystemComponentConstants.h
  
![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/6ea91696-f846-41c2-9d21-47c81c8ef770)

- GameObjectSystemComponentConstants.cpp
  
![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/41e45dc1-d9c7-4d68-8681-1477da3d5b3a)

The components will be added by loading in the **ObjectData.json** file in **data** folder.

![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/b6924e2a-30da-4ebb-977e-d4a5c7691a72)

Component details can be added in **GameObject.cpp**

![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/f619b738-1a5b-4bd5-a86d-c8f219b8db41)

## Adding events:

  New events can be added in **Event.h** file. 
  
  ![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/51fb89b7-e5dd-4084-b324-7c6ad621cd21)

  Callback functions should be registered in order to use the event.

  ![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/edd60319-c5f7-4cad-a081-10137ac3a7ce)
  
  Where _m_sceneChangeCallback_ is an EventHandler type and can be initialized as:
  
  ![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/1ed7a234-d29c-44a0-b785-14debbc25358)

  Events should be unsubscribed after done using 

  ![image](https://github.com/Picbridge/CustomGameEngine/assets/34910988/2db7453d-3609-47c7-aab1-1b35c9ca7614)






