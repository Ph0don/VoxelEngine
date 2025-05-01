#pragma once
#include <glad/glad.h>

namespace Vox
{

    class IndexBuffer
    {
    public:
        IndexBuffer(const void* indices, GLsizeiptr size);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        GLsizei GetCount() const { return m_Count; }

    private:
        GLuint m_IBO;
        GLsizei m_Count;
    };

}