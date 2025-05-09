#pragma once

#include "Rendering/Renderer.h"
#include "Utility/AssetTracker.h"

struct GLFWwindow;

namespace Vox
{

    struct AppSpec
    {
        const char* name;
        int width;
        int height;
    };

    class Application
    {
    public:
        Application(const AppSpec& spec);
        ~Application();

        void Run();

        static Application* Get();

        AssetTracker& GetAssetTracker();

    private:
        GLFWwindow* m_Window;
        bool m_Running;

        std::unique_ptr<Renderer> m_Renderer;

        AssetTracker m_AssetTracker;

        glm::vec3 m_Position;
        float m_Rotation;
    };

}