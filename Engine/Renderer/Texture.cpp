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

        // va_arg - accesses the next variadic function arguments
        Renderer& renderer = va_arg(args, Renderer);

        // va_end - ends traversal of the variadic function arguments
        va_end(args);

        // create texture (returns true/false if successful)
        return Load(filename, renderer);
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer) {
        return true;
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer) {
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

        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // !! call SDL_FreeSurface with surface as the parameter
        // !! no need to keep surface after texture is created
        SDL_FreeSurface(surface);

        return true;
    }

    Ethrl::Vector2 Texture::GetSize() const {
        return Vector2{ 0, 0 };
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