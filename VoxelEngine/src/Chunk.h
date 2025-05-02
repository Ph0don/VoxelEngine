#pragma once
#include <array>
#include <glm/glm.hpp>

#include "Voxel.h"

namespace Vox
{

    class Chunk
    {
    public:


    public:
        static constexpr int s_ChunkSize = 8;
    private:
        std::array<VoxelType, s_ChunkSize * s_ChunkSize * s_ChunkSize> m_VoxelData;
        glm::vec3 m_Position;
    };

}