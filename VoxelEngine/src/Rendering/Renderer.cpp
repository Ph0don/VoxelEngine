#include "Renderer.h"

#include <glad/glad.h>

namespace Vox
{
    void Renderer::StartFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void Renderer::EndFrame()
    {
    }
    void Renderer::SetClearColor(const glm::vec3& color)
    {
        m_ClearColor = color;
        glClearColor(color.r, color.g, color.b, 1.0f);
    }
    void Renderer::SetRendererMode(RendererMode mode)
    {
        m_RendererMode = mode;
    }
}