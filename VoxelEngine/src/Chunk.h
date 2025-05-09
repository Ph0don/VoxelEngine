#pragma once
#include <array>
#include <glm/glm.hpp>

#include "Voxel.h"

namespace Vox
{

    struct Chunk
    {
    public:
        Chunk(const glm::vec3& pos, VoxelType type = VoxelType::Air)
            :Position(pos), VoxelData()
        {
            memset(&VoxelData, (int)type, VoxelData.size() * sizeof(VoxelType));
        }
        ~Chunk() = default;

    public:
        static constexpr int s_ChunkSize = 8;

        std::array<VoxelType, s_ChunkSize * s_ChunkSize * s_ChunkSize> VoxelData;
        glm::vec3 Position;
    };

}