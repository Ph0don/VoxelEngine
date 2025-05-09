#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace Vox
{
    Texture::Texture(const std::filesystem::path& path)
        : m_Width(0), m_Height(0), m_Channels(0), m_TextureHandle(0)
    {
        stbi_set_flip_vertically_on_load(true);

        std::string pathStr = path.string();

        unsigned char* buffer = stbi_load(pathStr.c_str(), &m_Width, &m_Height, &m_Channels, 4);

        glGenTextures(1, &m_TextureHandle);

        Bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (buffer)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture: " << pathStr << std::endl;
        }
        stbi_image_free(buffer);
    }
    Texture::~Texture()
    {
        glDeleteTextures(1, &m_TextureHandle);
    }
    void Texture::Bind(int textureSlot)
    {
        glActiveTexture(GL_TEXTURE0 + textureSlot);
        glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
    }
}