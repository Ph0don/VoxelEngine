#include "IndexBuffer.h"

namespace Vox
{
    IndexBuffer::IndexBuffer(const void* indices, GLsizeiptr size)
        : m_IBO(0), m_Count(size / sizeof(GLuint))
    {
        glGenBuffers(1, &m_IBO);

        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }
    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_IBO);
    }
    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    }
    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}