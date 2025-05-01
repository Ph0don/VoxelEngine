#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <array>
#include "Geometry/Vertex.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"

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

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
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

        std::array<PosVertex, 3> vertices =
        {
            PosVertex{ -0.5f, -0.5f, 0.0f },
            PosVertex{ 0.5f, -0.5f, 0.0f },
            PosVertex{ 0.0f,  0.5f, 0.0f }
        };

        VertexBuffer vb(&vertices, sizeof(vertices));
        VertexArray vao;
        vao.AddBuffer<PosVertex>(vb);

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

        Shader shader(workingDir / "res" / "Color.vert", workingDir / "res" / "Color.frag");
        shader.Bind();

        while (m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            vao.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwPollEvents();
            if (glfwWindowShouldClose(m_Window))
            {
                m_Running = false;
            }

            glfwSwapBuffers(m_Window);
        }
    }
}