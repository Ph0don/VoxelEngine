#include "Renderer.h"

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexArray.h"

#include "../Geometry/NaiveMesher.h"

#include <iostream>

namespace Vox
{
    Renderer::Renderer()
    {
        m_RendererMode = RendererMode::Naive;
        m_ClearColor = glm::vec3(0.0f, 0.0f, 0.0f);
        m_Meshers[static_cast<int>(RendererMode::Naive)] = std::make_unique<NaiveMesher>();

        

    }
    Renderer::~Renderer()
    {
        if (m_Mesh != nullptr)
        {
            delete m_Mesh;
            m_Mesh = nullptr;
        }
    }
    void Renderer::StartFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    void Renderer::EndFrame()
    {
    }
    void Renderer::RenderChunk(const Chunk& chunk, const std::array<Chunk, 6>& surroundingChunks)
    {
        if (m_Mesh == nullptr)
        {
            auto [verts, size] = m_Meshers[static_cast<int>(m_RendererMode)]->MeshChunk(chunk, surroundingChunks);
            std::array<GLuint, s_indicesPerChunk> indices;
            uint32_t indexCount = static_cast<uint32_t>(static_cast<float>(size) / sizeof(VoxelVertex) * 1.5f);
            PopulateGenericIndexBuffer(indices, indexCount);
            m_Mesh = new Mesh(verts, size, indices.data(), indexCount * sizeof(GLuint));
        }
        m_Mesh->Render();


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
    void Renderer::PopulateGenericIndexBuffer(std::array<GLuint, s_indicesPerChunk>& indices, uint32_t indexCount)
    {
        for (GLuint i = 0, j = 0; i < indexCount; i+= 6, j += 4)
        {
            indices[i] = 0 + j;
            indices[i+1] = 1 + j;
            indices[i+2] = 2 + j;

            indices[i+3] = 2 + j;
            indices[i+4] = 3 + j;
            indices[i+5] = 0 + j;
        }
    }
}