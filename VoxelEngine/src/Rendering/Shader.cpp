#include "Shader.h"

#include <fstream>

namespace Vox
{

    Shader::Shader(const std::filesystem::path& vertSource, const std::filesystem::path& fragSource)
        : m_Program(0)
    {
        std::string vertCode = LoadShaderFile(vertSource);
        std::string fragCode = LoadShaderFile(fragSource);

        GLuint vertShader = CompileShader(vertCode.c_str(), GL_VERTEX_SHADER);
        GLuint fragShader = CompileShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

        m_Program = glCreateProgram();

        glAttachShader(m_Program, vertShader);
        glAttachShader(m_Program, fragShader);

        glLinkProgram(m_Program);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_Program);
    }

    void Shader::Bind()
    {
        glUseProgram(m_Program);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    std::string Shader::LoadShaderFile(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::ate);

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::string fileCode;
        fileCode.resize(fileSize);

        file.seekg(std::ios::beg);
        file.read(fileCode.data(), fileSize);

        file.close();

        return fileCode;
    }

    GLuint Shader::CompileShader(const char* shaderCode, GLenum type)
    {
        GLuint shader;
        shader = glCreateShader(type);

        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);

        return shader;
    }

}