#pragma once

#include <array>

#include "../Rendering/VertexBuffer.h"
#include "../Chunk.h"

namespace Vox
{

    class Mesher
    {
    public:
        virtual std::pair<void*, GLsizeiptr> MeshChunk(const Chunk& chunk, const std::array<Chunk, 6>& surroundingChunks) = 0;

    protected:
        static constexpr float s_VoxelSize = 1.f;
    };

}