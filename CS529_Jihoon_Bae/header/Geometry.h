/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Geometry.h>
Purpose: <Geometry class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/22/2023>
--------------------------------------------------------*/
#pragma once
class Material;
struct VertexData
{
    std::vector<glm::vec3> vertexBuffer;
    std::vector<glm::vec3> normalBuffer;//For 3D engine conversion ***Not used
};

class Geometry
{
public:

    Geometry();
    virtual ~Geometry();

    //-------------------
    // buffer assignment
    
    // @brief for 3D engine conversion ***Not used
    virtual void SetNormalBuffer(std::vector<glm::vec3> normalBuffer);

    // @brief assign the vertex buffer for current geometry
    // @param ertexBuffer: define the vertex buffer to use on render
    virtual void SetVertexBuffer(std::vector<glm::vec3> vertex);
    //-------------------

    //-------------------
    // rendering properties

    // @brief define the atrribute location to pass the vertex data
    // @param material: curent node material for getting shader
    virtual void SetupVertexAttributes(Material* material);

    // @brief binds the current vertex data to pass them to the shader program
    virtual void Bind();

    // @brief unbind the buffer for next geometry 
    virtual void Unbind();
    //-------------------

    //-------------------
    // getter function

    virtual VertexData* GetVertexData() { return &m_vertexData; }
    //-------------------

protected:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_IBO;

    VertexData m_vertexData;
};

