#pragma once

#define PI 3.14159265f
#define GLFW_INCLUDE_NONE
//-----------------
// standard library
#include <iostream>//exit,cout
#include <string>
#include <vector>//vector
#include <cmath>//sqrt
#include <fstream>
#include <sstream>//stringstream
#include <unordered_map>
#include <algorithm>
#include <array>
#include <stack>
#include <queue>
#include <random>
#include <chrono>//frame rate control
#include <thread>//frame rate control
#include <functional>
//------------------
// opengl library
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glew/glew.h>
#include <glfw/glfw3.h>//GLFW
#include "glm/mat4x4.hpp" 
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.inl"//Rotate
#include "glm/gtx/euler_angles.hpp"
//------------------
// rapidjson library
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
//-----------------
//Utility 
#include "Utils.h"
#include "GameObjectSystemComponentConstants.h"
#include "VectorCalculation.h"
#include "LevelsConstants.h"
#include "FrameRateController.h"
#include "Timer.h"
//-------------------
// custom vector and matrix
#include "Vector3D.h"
#include "Matrix3D.h"
//-----------------
// event
#include "Event.h"
#include "EventManager.h"
//-------------------
// render
#include "lodepng.h"
#include "Window.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"
#include "Geometry.h"
#include "Node.h"
#include "SceneGraph.h"
#include "Renderer.h"
#include "TriangleMesh.h"
#include "SquareMesh.h"
//-------------------
// input
#include "InputKeys.h"
#include "InputManager.h"
//-------------------
// physics
#include "Body.h"
#include "Shape.h"
#include "CollisionGenerator.h"
#include "Circle.h"
#include "AABB.h"
#include "OBB.h"
#include "PhysicsManager.h"

#include "CollisionFunctions.h"
//-------------------
//GameObject
#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
//-------------------
//Data driven
#include "GameObjectFactory.h"
#include "GameResourceFactory.h"
//-------------------
//Custom Components
#include "PlayerController.h"
#include "Follow.h"
#include "Behavior.h"
#include "Weapon.h"
#include "EnemyBehavior.h"
//Game
//-------------------
#include "Root.h"
#include "Scene.h"
#include "Engine.h"
#include "Game.h"
//Levels
//-------------------
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"