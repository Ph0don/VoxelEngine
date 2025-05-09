#include "Mesh.h"

namespace Vox
{

    Mesh::Mesh(void* vertexData, GLsizeiptr vertSize, void* indexData, GLsizeiptr indiciesSize)
        : m_VertexBuffer(vertexData, vertSize),
        m_IndexBuffer(indexData, indiciesSize),
        m_VertexArray()
    {
        m_VertexArray.Bind();
        m_VertexBuffer.Bind();
        m_IndexBuffer.Bind();

        // Set the vertex attributes
        m_VertexArray.AddBuffer<VoxelVertex>(m_VertexBuffer);

        m_VertexArray.Unbind();
    }
    Mesh::~Mesh()
    {
        m_VertexArray.Unbind();
        m_IndexBuffer.Unbind();
        m_VertexBuffer.Unbind();
    }
    void Mesh::Render() const
    {
        //m_VertexBuffer.Bind();
        m_VertexArray.Bind();
        m_IndexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, (GLvoid*)0);

        //m_VertexBuffer.Unbind();
        m_VertexArray.Unbind();
        m_IndexBuffer.Unbind();
    }
}