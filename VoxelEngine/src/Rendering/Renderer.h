#pragma once
#include <memory>

#include <glm/glm.hpp>

#include "../Chunk.h"
#include "../Geometry/Mesher.h"

#include "../Geometry/Mesh.h"

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
        Renderer();
        ~Renderer();

        void StartFrame();
        void EndFrame();

        void RenderChunk(const Chunk& chunk, const std::array<Chunk, 6>& surroundingChunks);

        void SetClearColor(const glm::vec3& color);
        void SetRendererMode(RendererMode mode);

    private:
        static constexpr int s_indicesPerChunk = 8 * 8 * 8 * 6 * 6;
        void PopulateGenericIndexBuffer(std::array<GLuint, s_indicesPerChunk>& indices, uint32_t indexCount);

    private:
        glm::vec3 m_ClearColor;
        RendererMode m_RendererMode;
        std::array<std::unique_ptr<Mesher>, 3> m_Meshers;

        Mesh* m_Mesh = nullptr;
    };

}