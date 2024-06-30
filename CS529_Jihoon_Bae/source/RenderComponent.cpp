#include "pch.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
    Shutdown();
}

void RenderComponent::Init()
{
    m_pMaterial = Renderer::GetInstance()->GetMaterial("Default");
    m_pGeometry = nullptr;
}

void RenderComponent::Update()
{
}

void RenderComponent::Shutdown()
{
    m_pGeometry->Unbind();
    m_pMaterial->Unbind();
    m_pMaterial->GetShader()->Unuse();

    if (m_pGeometry != nullptr)
    {
        m_pGeometry->Unbind();
        delete m_pGeometry;
    }
}

void RenderComponent::HandleEvent(const Event& e)
{

}

void RenderComponent::Draw()
{
    if (GetOwner()->NeedsDeletion()) return;
	Transform* transform = GetOwner()->GetTransform();

    m_pMaterial->GetShader()->Use();
    m_pGeometry->Bind();

    m_pMaterial->GetShader()->SetUniform("model", GetOwner()->GetWorldTransform());
    m_pMaterial->GetShader()->SetUniform("view", transform->GetView());
    m_pMaterial->GetShader()->SetUniform("projection", transform->GetProjection());
    m_pMaterial->GetShader()->SetUniform("localModel", transform->GetModel());
    m_pGeometry->SetupVertexAttributes(m_pMaterial);
    m_pMaterial->SetupUniformData();
    m_pMaterial->Bind();
    // Draw the triangle
    glDisable(GL_DEBUG_OUTPUT);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_pGeometry->GetVertexData()->vertexBuffer.size());
    m_pGeometry->Unbind();
    m_pMaterial->Unbind();
    m_pMaterial->GetShader()->Unuse();
}

void RenderComponent::SetColor(glm::vec3 color)
{
    m_pMaterial->SetColor(color);
}

void RenderComponent::SetMaterial(Material* material)
{
    m_pMaterial = material;
}

void RenderComponent::SetShader(Shader* shader)
{
    if (!m_pMaterial) return;
    m_pMaterial->SetShader(shader);
}

void RenderComponent::SetGeometry(const std::string& geometryName)
{
    if (geometryName == "TriangleMesh")
        SetGeometry<TriangleMesh>();
    // add on as mesh type gets added
    if (geometryName == "SquareMesh")
        SetGeometry<SquareMesh>();
}