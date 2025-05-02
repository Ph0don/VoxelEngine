#pragma once

#include "Rendering/Renderer.h"

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

    private:
        GLFWwindow* m_Window;
        bool m_Running;

        Renderer m_Renderer;
    };

}