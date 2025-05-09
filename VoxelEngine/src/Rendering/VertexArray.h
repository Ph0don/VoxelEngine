#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"

namespace Vox
{

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        template<typename T>
        void AddBuffer(const VertexBuffer& buffer);

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_VAO;
    };

    template<typename T>
    inline void VertexArray::AddBuffer(const VertexBuffer& buffer)
    {
        VertexLayout layout = std::move(VertexLayout::GetLayout<T>());

        Bind();
        buffer.Bind();

        const auto& attribs = layout.GetAttributes();
        GLuint offset = 0;

        for (size_t i = 0; i < attribs.size(); ++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribs[i].Size, attribs[i].Type, attribs[i].Normalized, layout.GetStride(), reinterpret_cast<void*>(offset));
            offset += attribs[i].Size * VertexAttribute::GetSizeOfType(attribs[i].Type);
        }
    }
}