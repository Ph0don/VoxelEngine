#include <filesystem>

#include <glad/glad.h>

namespace Vox
{

    class Shader
    {
    public:
        Shader(const std::filesystem::path& vertSource, const std::filesystem::path& fragSource);
        ~Shader();

        void Bind();
        void Unbind();

    private:
        std::string LoadShaderFile(const std::filesystem::path& path);
        GLuint CompileShader(const char* shaderCode, GLenum type);

    private:
        GLuint m_Program;
    };

}