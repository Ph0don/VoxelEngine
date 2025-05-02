#include "Shader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

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

    void Shader::SetUniformFloat(const char* name, float val)
    {
        GLint loc = GetUniformLocation(name);

        glUniform1f(loc, val);
    }

    void Shader::SetUniformVec2(const char* name, const glm::vec2& val)
    {
        GLint loc = GetUniformLocation(name);

        glUniform2fv(loc, 1, glm::value_ptr(val));
    }

    void Shader::SetUniformVec3(const char* name, const glm::vec3& val)
    {
        GLint loc = GetUniformLocation(name);

        glUniform3fv(loc, 1, glm::value_ptr(val));
    }

    void Shader::SetUniformVec4(const char* name, const glm::vec4& val)
    {
        GLint loc = GetUniformLocation(name);

        glUniform4fv(loc, 1, glm::value_ptr(val));
    }

    void Shader::SetUniformMat4(const char* name, const glm::mat4& val)
    {
        GLint loc = GetUniformLocation(name);

        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
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

    GLint Shader::GetUniformLocation(const char* name) const
    {
        if (m_UniformCache.find(name) != m_UniformCache.end())
            return m_UniformCache[name];

        GLint loc = glGetUniformLocation(m_Program, name);
        m_UniformCache[name] = loc;

        return loc;
    }

}