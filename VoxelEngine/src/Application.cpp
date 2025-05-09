#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <array>
#include "Geometry/Vertex.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

#include "Geometry/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vox
{

    static Application* s_Instance = nullptr;

    Application::Application(const AppSpec& spec)
        : m_Window(nullptr), m_Running(true), m_AssetTracker(), m_Position(0.0f), m_Rotation(0.0f), m_Renderer(nullptr)
    {
        if (s_Instance == nullptr)
        {
            s_Instance = this;
        }
        else
        {
            std::cerr << "More than one instance of application running!";
        }

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

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
            });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize OpenGL Context" << std::endl;
            return;
        }
        m_Renderer = std::make_unique<Renderer>();

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
            VoxelVertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2( 0.f, 0.f),  glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
            VoxelVertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.f, 0.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
            VoxelVertex{ glm::vec3(0.5f,  0.5f, 0.0f), glm::vec2(1.f, 1.f),    glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
            VoxelVertex{ glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.f, 1.f),   glm::vec4(16.0f / 128.f,   112 / 128.f, 16.f / 128.f, 16.f / 128.f), glm::vec2(1.0,1)},
        };

        std::array<GLuint, 6> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

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

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Chunk chunk(glm::vec3(0.0f), VoxelType::Dirt);

        Mesh mesh(vertices.data(), sizeof(vertices), indices.data(), sizeof(indices));

        while (m_Running)
        {
            m_Renderer->StartFrame();

            auto nowTime = std::chrono::high_resolution_clock::now();

            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - begTime);

            shader.RebuildIfDirty();
            shader.Bind();

            glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f, 1.f, 1.f));

            shader.SetUniformMat4("u_Model", model);

            glm::mat4 view = glm::translate(glm::identity<glm::mat4>(), -1.0f * m_Position);
            view = glm::rotate(view, m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f));
            shader.SetUniformMat4("u_View", view);

            glm::mat4 proj = glm::perspective(45.0f, width / (float)height, 0.1f, 100.0f);
            shader.SetUniformMat4("u_Proj", proj);

            //shader.SetUniformFloat("u_col", sinf(milliseconds.count() * 0.01f));
            std::array surroundingChunks = {
                Chunk(glm::vec3(0.0f), VoxelType::Dirt),
                Chunk(glm::vec3(0.0f), VoxelType::Dirt),
                Chunk(glm::vec3(0.0f), VoxelType::Dirt),
                Chunk(glm::vec3(0.0f), VoxelType::Dirt),
                Chunk(glm::vec3(0.0f), VoxelType::Dirt),
                Chunk(glm::vec3(0.0f), VoxelType::Dirt)
            };

            if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
            {
                m_Position.z -= 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
            {
                m_Position.z += 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
            {
                m_Position.x -= 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
            {
                m_Position.x += 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                m_Position.y += 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                m_Position.y -= 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                m_Rotation -= 0.1f;
            }
            if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
            {
                m_Rotation += 0.1f;
            }


            mesh.Render();
            
            model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
            shader.SetUniformMat4("u_Model", model);

            //glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (GLvoid*)0);
            mesh.Render();

            
            m_Renderer->RenderChunk(chunk, surroundingChunks);

            m_Renderer->EndFrame();

            glfwPollEvents();
            if (glfwWindowShouldClose(m_Window))
            {
                m_Running = false;
            }

            glfwSwapBuffers(m_Window);

        }
    }
    Application* Application::Get()
    {
        return s_Instance;
    }
    AssetTracker& Application::GetAssetTracker()
    {
        return m_AssetTracker;
    }
}