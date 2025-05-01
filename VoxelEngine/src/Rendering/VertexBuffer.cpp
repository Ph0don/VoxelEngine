#include "VertexBuffer.h"

namespace Vox
{

    VertexBuffer::VertexBuffer(const void* data, GLsizeiptr size)
    {
        glGenBuffers(1, &m_VBO);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}