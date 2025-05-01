#pragma once

#include <vector>
#include <stdexcept>

struct Vertex {};
struct PosVertex : public Vertex
{
    float x, y, z;

    PosVertex(float posX, float posY, float posZ) : x(posX), y(posY), z(posZ) {}
};

struct VertexAttribute
{
    GLuint Type;
    GLint Size;
    GLboolean Normalized;

    static GLsizei GetSizeOfType(GLuint type)
    {
        switch (type)
        {
        case GL_DOUBLE: return sizeof(GLdouble);

        case GL_HALF_FLOAT: return sizeof(GLhalf);
        case GL_FLOAT: return sizeof(GLfloat);

        case GL_INT: return sizeof(GLint);
        case GL_UNSIGNED_INT: return sizeof(GLuint);

        case GL_SHORT: return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);

        case GL_BYTE: return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
    }
};

class VertexLayout
{
public:
    template<typename T> 
    void Push(int count)
    {
        throw std::runtime_error("Unsupported type");
    }

    template<>
    void Push<float>(int count)
    {
        m_Attribs.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += VertexAttribute::GetSizeOfType(GL_FLOAT) * count;
    }
    template<>
    void Push<int>(int count)
    {
        m_Attribs.push_back({ GL_INT, count, GL_FALSE });
        m_Stride += VertexAttribute::GetSizeOfType(GL_INT) * count;
    }
    template<>
    void Push<unsigned int>(int count)
    {
        m_Attribs.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += VertexAttribute::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }
    template<>
    void Push<char>(int count)
    {
        m_Attribs.push_back({ GL_BYTE, count, GL_FALSE });
        m_Stride += VertexAttribute::GetSizeOfType(GL_BYTE) * count;
    }
    template<>
    void Push<unsigned char>(int count)
    {
        m_Attribs.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += VertexAttribute::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    GLsizei GetStride() const { return m_Stride; }
    const std::vector<VertexAttribute>& GetAttributes() const { return m_Attribs; }

    template<typename T>
    static VertexLayout GetLayout()
    {
        static_assert(std::is_base_of_v<Vertex, T> == true && "Provided type must derive from vertex!");
    }

    template<>
    static VertexLayout GetLayout<PosVertex>()
    {
        VertexLayout layout;
        layout.Push<float>(3);

        return layout;
    }

public:
    VertexLayout() = default;
    ~VertexLayout() = default;

    VertexLayout& operator=(VertexLayout&& other) noexcept
    {
        m_Attribs = std::move(other.m_Attribs);
        m_Stride = std::move(other.m_Stride);
    }

    VertexLayout(VertexLayout&& other) noexcept
    {
        m_Attribs = std::move(other.m_Attribs);
        m_Stride = std::move(other.m_Stride);
    }

private:
    std::vector<VertexAttribute> m_Attribs;
    GLsizei m_Stride = 0;
};

