#pragma once
#include <glad/glad.h>
#include "../Geometry/Vertex.h"

namespace Vox
{

    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, GLsizeiptr size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_VBO;
    };

}