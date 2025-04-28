#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <array>
#include "Geometry/Vertex.h"
#include "Shader.h"

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

        std::array<Vertex, 3> vertices =
        {
            Vertex{ -0.5f, -0.5f, 0.0f },
            Vertex{ 0.5f, -0.5f, 0.0f },
            Vertex{ 0.0f,  0.5f, 0.0f }
        };

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);

        GLuint vertexArray;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3.0f * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

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

            glBindVertexArray(vertexArray);
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