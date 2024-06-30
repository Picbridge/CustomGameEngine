/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Renderer.h>
Purpose: <Responsible for initializing the OpenGL context, 
creating shaders, and managing rendering state.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/24/2023>
--------------------------------------------------------*/
#pragma once
// manage the addition/deletion of the shader and materials
// indirectly manages the object entity through SceneGraph*
class Renderer
{
public:
	Renderer();
	~Renderer();
	
	static Renderer* GetInstance();

	void Init();

	//@brief render function gets called per frame
	void Render();
	//-------------------
	// external asset control

	// @brief adds the user defined shader from the path provided
	// @param name: shader name that will be stored in the shader map
	// @param vertexPath: path and file name for the vertex shader
	// @param fragmentPath: path and file name for the fragment shader
	// @param geometryPath: path and file name for the geometry shader(if any)
	void AddShader(const std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// @brief removes the shader from the engine
	// @param name: name of the shader to remove
	void RemoveShader(const std::string name);

	// @brief adds the new material for user to define
	// @param name: material name that will be stored in the material map
	void AddMaterial(const std::string name, const char* diffuse = nullptr, const char* specular = nullptr);

	// @brief removes the material from the engine
	// @param name: material name to remove
	void RemoveMaterial(const std::string name);

	//-------------------

	//-------------------
	// getter functions

	Shader* GetShader(const std::string name){ return shaders[name]; }
	Material* GetMaterial(const std::string name){ return materials[name]; }
	SceneGraph& GetSceneGraph() { return *m_sceneGraph; }
	GLFWwindow* GetWindow() { return WindowHandler::GetInstance().GetCurrentContext(); }
	//-------------------

private:
	static Renderer* instance;
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Material*> materials;
	SceneGraph* m_sceneGraph;
	void getGLError();

};

