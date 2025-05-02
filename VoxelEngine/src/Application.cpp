#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <array>
#include "Geometry/Vertex.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vox
{
    Application::Application(const AppSpec& spec)
        : m_Window(nullptr), m_Running(true)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        m_Window = glfwCreateWindow(spec.width, spec.height, spec.name, nullptr, nullptr);

        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                glViewport(0, 0, width, height);
            });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize OpenGL Context" << std::endl;
            return;
        }

#if _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
    }
    Application::~Application()
    {
        if (m_Window)
        {
            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }
    }
    void Application::Run()
    {
        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        std::array<VoxelVertex, 4> vertices =
        {
            VoxelVertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2( 0.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(2.0,1)},
            VoxelVertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(2.0,1)},
            VoxelVertex{ glm::vec3(0.5f,  0.5f, 0.0f), glm::vec2(1.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(2.0,1)},
            VoxelVertex{ glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(2.0,1)},
        };

        std::array<GLuint, 6> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        VertexBuffer vb(&vertices, sizeof(vertices));
        IndexBuffer  ib(&indices, sizeof(indices));

        VertexArray vao;
        vao.AddBuffer<VoxelVertex>(vb);

        std::filesystem::path workingDir;
        if (_DEBUG)
        {
            workingDir = std::filesystem::current_path() / ".." / ".." / "VoxelEngine";
        }
        else
        {
            workingDir = std::filesystem::current_path();
        }

        std::filesystem::current_path(workingDir);

        Shader shader(workingDir / "res" / "shaders" / "Color.vert", workingDir / "res"/ "shaders" / "Color.frag");
        shader.Bind();

        Texture tex(workingDir / "res" / "textures" / "SpriteAtlas.png");
        tex.Bind();

        auto begTime = std::chrono::high_resolution_clock::now();

        int width = 0, height = 0;
        glfwGetWindowSize(m_Window, &width, &height);

        glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(10.0f,5.f,1.f));

        shader.SetUniformMat4("u_Model", model);

        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 15.0f), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        shader.SetUniformMat4("u_View", view);

        glm::mat4 proj = glm::perspective(45.0f, width / (float)height, 0.1f, 100.0f);
        shader.SetUniformMat4("u_Proj", proj);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        while (m_Running)
        {
            m_Renderer.StartFrame();

            auto nowTime = std::chrono::high_resolution_clock::now();

            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - begTime);

            shader.SetUniformFloat("u_col", sinf(milliseconds.count() * 0.01f));

            vao.Bind();
            ib.Bind();
            glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (GLvoid*)0);

            glfwPollEvents();
            if (glfwWindowShouldClose(m_Window))
            {
                m_Running = false;
            }

            glfwSwapBuffers(m_Window);

            m_Renderer.EndFrame();
        }
    }
}