/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Renderer.cpp>
Purpose: <Responsible for initializing the OpenGL context,
creating shaders, and managing rendering state.>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/24/2023>
--------------------------------------------------------*/
#include "pch.h"
// set as singleton
Renderer* Renderer::instance = nullptr;

Renderer::Renderer() : m_sceneGraph(new SceneGraph())
{
}

Renderer::~Renderer()
{
    for (auto kv : shaders)
    {
        kv.second->Unuse();
        delete kv.second;
    }
}

Renderer* Renderer::GetInstance()
{
    if (!instance) {
        instance = new Renderer();
    }
    return instance;
}

void Renderer::Init()
{
    shaders["Default"] = new Shader("shader/VertexShader.vs", "shader/FragmentShader.fs");
    materials["Default"] = new Material(shaders["Default"]);
    std::cout << "Render System Initialized" << std::endl;
}

void Renderer::Render() 
{
    // render all allocated nodes in the scene with geometry (nodes have transform and material as default, but not geometry)
    //for (auto node : m_sceneGraph->nodes) --> Moved to RenderComponent
    //{
    //    Geometry* geometry = node->GetGeometry();
    //    Material* material = node->GetMaterial();
    //    Transform* transform = node->GetTransform();

    //    if (geometry && material && transform)
    //    {
    //        material->GetShader()->Use();
    //        geometry->Bind();
    //
    //        material->GetShader()->SetUniform("model", node->GetWorldTransform());
    //        material->GetShader()->SetUniform("view", transform->GetView());
    //        material->GetShader()->SetUniform("projection", transform->GetProjection());
    //        material->GetShader()->SetUniform("rotationMatrix", transform->GetModel());
    //        geometry->SetupVertexAttributes(material);
    //        material->SetupUniformData();
    //        material->Bind();
    //        // Draw the triangle
    //        glDrawArrays(GL_TRIANGLES, 0, 3);
    //        getGLError();
    //        geometry->Unbind();
    //        material->Unbind();
    //    }
    //    
    //}
}

void Renderer::AddShader(const std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    shaders[name] = new Shader(vertexPath, fragmentPath, geometryPath);
}

void Renderer::RemoveShader(const std::string name)
{
    auto it = shaders.find(name);
    std::vector<decltype(shaders)::key_type> keysToDelete;

    // free the data and erase from the map
    if (it != shaders.end())
    {
        it->second->Unuse();
        delete it->second;
        keysToDelete.push_back(it->first);
    }

    for (auto key : keysToDelete)
        shaders.erase(key);
}

void Renderer::AddMaterial(const std::string name, const char* diffuse, const char* specular)
{
    materials[name] = new Material();
    if (diffuse)
        materials[name]->SetTextureDiffuse(diffuse);
    if (specular)
        materials[name]->SetTextureSpecular(specular);
}

void Renderer::RemoveMaterial(const std::string name)
{
    auto it = materials.find(name);

    //free the data and erase from the map
    if (it != materials.end())
    {
        if (it->second != nullptr)
            delete it->second;
        materials.erase(it);
    }
}

void Renderer::getGLError()
{
    GLenum err = glGetError();
    if (GLEW_OK != err)
    {
        std::cout << "Terminating program. Reason:" << std::endl;
        std::cout << "Error in GLEW: " << glewGetErrorString(err) << std::endl;
        //exit(EXIT_FAILURE);
    }
}