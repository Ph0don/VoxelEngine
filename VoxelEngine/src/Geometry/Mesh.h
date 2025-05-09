#pragma once

#include "../Rendering/VertexBuffer.h"
#include "../Rendering/IndexBuffer.h"
#include "../Rendering/VertexArray.h"

namespace Vox
{

    class Mesh
    {
    public:
        Mesh(void* vertexData, GLsizeiptr vertSize, void* indexData, GLsizeiptr indiciesSize);
        ~Mesh();

        void Render() const;

    private:
        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;
        VertexArray m_VertexArray;

    };

}