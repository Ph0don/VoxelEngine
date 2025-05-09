#pragma once

#include "Mesher.h"
#include "../Chunk.h"

namespace Vox
{

    class NaiveMesher : public Mesher
    {

    public:
        virtual std::pair<void*, GLsizeiptr> MeshChunk(const Chunk& chunk, const std::array<Chunk, 6>& surroundingChunks) override;

        std::vector<VoxelVertex> m_Vertices;
    };

}