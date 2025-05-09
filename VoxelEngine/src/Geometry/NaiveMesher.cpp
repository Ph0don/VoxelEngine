#include "NaiveMesher.h"

namespace Vox
{

    static std::array<VoxelVertex, 24> s_CubeVerts =
    {
        VoxelVertex{ glm::vec3(1.f, 0.f, 0.0f), glm::vec2(0.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 0.0f), glm::vec2(1.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 1.f, 0.0f), glm::vec2(0.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},

        VoxelVertex{ glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 0.f, 1.0f), glm::vec2(1.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 1.f, 1.0f), glm::vec2(1.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 1.0f), glm::vec2(0.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        //
        //left
        VoxelVertex{ glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 0.f, 1.0f), glm::vec2(1.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 1.0f), glm::vec2(1.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 0.0f), glm::vec2(0.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        //right
        VoxelVertex{ glm::vec3(1.f, 0.f, 1.0f), glm::vec2(0.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 1.f, 0.0f), glm::vec2(1.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 1.f, 1.0f), glm::vec2(0.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        //
        //bottom
        VoxelVertex{ glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 0.f, 0.0f), glm::vec2(1.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 0.f, 1.0f), glm::vec2(1.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 0.f, 1.0f), glm::vec2(0.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        //
        //top
        VoxelVertex{ glm::vec3(1.f, 1.f, 0.0f), glm::vec2(0.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 0.f), glm::vec2(1.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(0.f, 1.f, 1.0f), glm::vec2(1.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        VoxelVertex{ glm::vec3(1.f, 1.f, 1.0f), glm::vec2(0.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
    };

        std::pair<void*, GLsizeiptr> NaiveMesher::MeshChunk(const Chunk & chunk, const std::array<Chunk, 6>& surroundingChunks)
    {
        glm::vec3 position = chunk.Position;

        m_Vertices.clear();

        constexpr float atlasSize = 128.f;
        constexpr float tileSize = 16.f;
        constexpr int tileCount = atlasSize / tileSize;
        constexpr float tileAtlasRatio = tileSize / atlasSize;

        for (int z = 0; z < Chunk::s_ChunkSize; z++)
        {
            for (int y = 0; y < Chunk::s_ChunkSize; y++)
            {
                for (int x = 0; x < Chunk::s_ChunkSize; x++)
                {
                    int index = x + Chunk::s_ChunkSize * (y + Chunk::s_ChunkSize * z);

                    if (chunk.VoxelData[index] == VoxelType::Air)
                        continue;

                    glm::vec3 basePos = position + glm::vec3(x * s_VoxelSize, y * s_VoxelSize, z * s_VoxelSize);

                    for (auto vert : s_CubeVerts)
                    {
                        vert.VoxelTiling = glm::vec2(1.0f, 1.0f);

                        float xOffset = ((int)chunk.VoxelData[index] - 1 % tileCount) * tileAtlasRatio;
                        float yOffset = (tileCount - (int)chunk.VoxelData[index] / tileCount) * tileAtlasRatio;

                        vert.AtlasTransforms = glm::vec4(xOffset, 112 / 128.f, tileAtlasRatio, tileAtlasRatio);

                        vert.Position = basePos + vert.Position * s_VoxelSize;
                        
                        m_Vertices.push_back(vert);
                    }
                }
            }
        }


        return { m_Vertices.data(), m_Vertices.size() * sizeof(VoxelVertex)};
    }

}