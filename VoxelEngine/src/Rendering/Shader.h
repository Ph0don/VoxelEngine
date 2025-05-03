#pragma once

#include <filesystem>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Vox
{

    class Shader
    {
    public:
        Shader(const std::filesystem::path& vertSource, const std::filesystem::path& fragSource);
        ~Shader();

        void Bind();
        void Unbind();

        void RebuildIfDirty();

        void SetUniformFloat(const char* name, float val);
        void SetUniformVec2(const char* name, const glm::vec2& val);
        void SetUniformVec3(const char* name, const glm::vec3& val);
        void SetUniformVec4(const char* name, const glm::vec4& val);
        void SetUniformMat4(const char* name, const glm::mat4& val);
        bool m_Dirty = false;

    private:
        GLuint ReloadShader();
        std::string LoadShaderFile(const std::filesystem::path& path);
        GLuint CompileShader(const char* shaderCode, GLenum type);

        GLint GetUniformLocation(const char* name) const;
    private:
        GLuint m_Program;
        std::filesystem::path m_VertSource;
        std::filesystem::path m_FragSource;

        mutable std::unordered_map<const char*, GLint> m_UniformCache;

    };

}