#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdarg>

namespace Ethrl {
    Texture::~Texture() {
        if (m_texture) glDeleteTextures(1, &m_texture);
    }

    bool Texture::Create(std::string filename, ...) {
        // va_list - type to hold information about variable arguments
        va_list args;

        // va_start - enables access to variadic function arguments
        va_start(args, filename);

        // va_end - ends traversal of the variadic function arguments
        va_end(args);

        // create texture (returns true/false if successful)
        return Load(filename);
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer) {
        return true;
    }

    bool Texture::CreateTexture(int width, int height) {
        m_target = GL_TEXTURE_2D;
        m_width = width;
        m_height = height;

        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        // create texture (width, height)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        return true;
    }

    bool Texture::CreateDepthTexture(int width, int height) {
        m_target = GL_TEXTURE_2D;
        m_width = width;
        m_height = height;

        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        // create texture (width, height)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        return true;
    }

    bool Texture::Load(const std::string& filename) {
        // load surface
        // !! call IMG_Load with c-string of filename
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr) {
            LOG(SDL_GetError());
            return false;
        }
        FlipSurface(surface);

        // create texture
        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        LOG("%s : width = %d | height = %d | pixel format = %s", filename.c_str(), surface->w, surface->h, SDL_GetPixelFormatName(surface->format->format));

        GLenum InternalFormat = GetInternalFormat(surface->format->format);
        GLint format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, InternalFormat, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

        SDL_FreeSurface(surface);

        return true;
    }

    GLenum Texture::GetInternalFormat(GLuint format) {
        GLenum InternalFormat = SDL_PIXELFORMAT_UNKNOWN;
        switch (format) {
        case SDL_PIXELFORMAT_RGB888:
        case SDL_PIXELFORMAT_RGB24:
            InternalFormat = GL_RGB;
            break;
        case SDL_PIXELFORMAT_BGR888:
        case SDL_PIXELFORMAT_BGR24:
            InternalFormat = GL_BGR;
            break;
        case SDL_PIXELFORMAT_RGBA8888:
        case SDL_PIXELFORMAT_RGBA32:
            InternalFormat = GL_RGBA;
            break;
        case SDL_PIXELFORMAT_BGRA8888:
        case SDL_PIXELFORMAT_BGRA32:
            InternalFormat = GL_BGRA;
            break;
        }
        return InternalFormat;
    }

    glm::ivec2 Texture::GetSize() const {
        return glm::ivec2{ m_width, m_height };
    }

    void Texture::FlipSurface(SDL_Surface* surface) {
        SDL_LockSurface(surface);

        int Pitch = surface->pitch; // Row Size
        uint8_t* Temp = new uint8_t[Pitch]; // Intermediate Buffer
        uint8_t* Pixels = (uint8_t*)surface->pixels;

        for (int i = 0; i < surface->h / 2; ++i) {
            uint8_t* Row1 = Pixels + i * Pitch;
            uint8_t* Row2 = Pixels + (surface->h - i - 1) * Pitch;

            // Swap Rows
            memcpy(Temp, Row1, Pitch);
            memcpy(Row1, Row2, Pitch);
            memcpy(Row2, Temp, Pitch);
        }
        delete[] Temp;

        SDL_UnlockSurface(surface);
    }
}