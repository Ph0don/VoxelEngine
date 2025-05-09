#include "Shader.h"

#include <fstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "../Application.h"

namespace Vox
{

    Shader::Shader(const std::filesystem::path& vertSource, const std::filesystem::path& fragSource)
        : m_Program(0), m_VertSource(vertSource), m_FragSource(fragSource)
    {
        m_Program = ReloadShader();
        Application::Get()->GetAssetTracker().AddModifiedCallback(vertSource, [=]() { m_Dirty = true; });
        Application::Get()->GetAssetTracker().AddModifiedCallback(fragSource, [=]() {  m_Dirty = true; });
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

    void Shader::RebuildIfDirty()
    {
        if (m_Dirty)
        {
            GLuint program = ReloadShader();
            if (program != 0)
            {
                glDeleteProgram(m_Program);
                m_Program = program;
                m_UniformCache.clear();
            }

            m_Dirty = false;
        }
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

    GLuint Shader::ReloadShader()
    {
        std::string vertCode = LoadShaderFile(m_VertSource);
        std::string fragCode = LoadShaderFile(m_FragSource);

        GLuint vertShader = CompileShader(vertCode.c_str(), GL_VERTEX_SHADER);
        if (vertShader == 0)
        {
            return 0;
        }

        GLuint fragShader = CompileShader(fragCode.c_str(), GL_FRAGMENT_SHADER);
        if (fragShader == 0)
        {
            return 0;
        }

        GLuint program = glCreateProgram();

        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            std::cerr << infoLog.data() << std::endl;

            return 0;
        }

        glDetachShader(program, vertShader);
        glDetachShader(program, fragShader);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return program;
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

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            std::cerr << infoLog.data() << std::endl;

            glDeleteShader(shader);

            return 0;
        }

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