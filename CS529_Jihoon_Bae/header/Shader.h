/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Shader.h>
Purpose: <Shader class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/21/2023>
--------------------------------------------------------*/
#pragma once

class Shader
{
public:
	 
	 // constructor generates the shader
	 Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	 //-------------------
	 // general shader function

	 //@brief activate the shader
	 void Use();

	 //@brief deactivate the shader
	 void Unuse();

	 // @brief returns the location of the attribute found in shader file
	 // @param name: attribute name to look up
	 // @return location id of the attribute
	 GLint GetAttributeLocation(const std::string& name);
	 //-------------------
	 
	 // utility uniform function
	 //-------------------

	 // @brief assign value to uniform in shader
	 // @param name: uniform variable name to assign value 
	 // @param value: vale to assign to the name of the uniform
	 template <typename T>
	 void SetUniform(const std::string& name, const T& value) {
		 GLint location = glGetUniformLocation(m_ID, name.c_str());

		 if constexpr (std::is_same_v<T, bool>) {
			 glUniform1i(location, static_cast<int>(value));
		 }
		 else if constexpr (std::is_same_v<T, int>) {
			 glUniform1i(location, value);
		 }
		 else if constexpr (std::is_same_v<T, float>) {
			 glUniform1f(location, value);
		 }
		 else if constexpr (std::is_same_v<T, glm::vec2>) {
			 glUniform2fv(location, 1, &value[0]);
		 }
		 else if constexpr (std::is_same_v<T, glm::vec3>) {
			 glUniform3fv(location, 1, &value[0]);
		 }
		 else if constexpr (std::is_same_v<T, glm::vec4>) {
			 glUniform4fv(location, 1, &value[0]);
		 }
		 else if constexpr (std::is_same_v<T, glm::mat2>) {
			 glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
		 }
		 else if constexpr (std::is_same_v<T, glm::mat3>) {
			 glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
		 }
		 else if constexpr (std::is_same_v<T, glm::mat4>) {
			 glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
		 }

		 getGLError();
	 }
	 //-------------------
private:
	GLuint m_ID;
	std::unordered_map<std::string, GLint> m_uniformLocations;
	void getGLError();
	// utility function for checking shader compilation/linking errors.
	void CheckCompileErrors(GLuint shader, std::string type);
};
