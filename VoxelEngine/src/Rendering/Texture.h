#pragma once
#include <cstdint>
#include <filesystem>
#include <glad/glad.h>

namespace Vox
{

    class Texture
    {
    public:
        Texture(const std::filesystem::path& path);
        ~Texture();

        int32_t GetWidth() const { return m_Width; }
        int32_t GetHeight() const { return m_Height; }
        int32_t GetChannels() const { return m_Channels; }

        void Bind(int textureSlot = 0);

    private:
        GLuint m_TextureHandle;

        int32_t m_Width;
        int32_t m_Height;
        int32_t m_Channels;
    };

}