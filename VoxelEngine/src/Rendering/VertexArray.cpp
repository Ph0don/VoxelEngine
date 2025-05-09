#include "VertexArray.h"

namespace Vox
{
    VertexArray::VertexArray():
        m_VAO(0)
    {
        glGenVertexArrays(1, &m_VAO);
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_VAO);
    }
    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}