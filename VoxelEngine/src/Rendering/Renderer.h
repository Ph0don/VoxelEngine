#pragma once

#include <glm/glm.hpp>

namespace Vox
{

    enum class RendererMode
    {
        Naive = 0,
        Culled = 1,
        Greedy
    };

    class Renderer
    {
    public:
        void StartFrame();
        void EndFrame();

        void SetClearColor(const glm::vec3& color);
        void SetRendererMode(RendererMode mode);

    private:
        glm::vec3 m_ClearColor;
        RendererMode m_RendererMode;
    };

}