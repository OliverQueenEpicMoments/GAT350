#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdarg>

namespace Ethrl
{
    Texture::~Texture() {
        // !! if texture not null SDL_DestroyTexture
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
        // destroy the current texture if one exists
        /*if (m_texture) SDL_DestroyTexture(m_texture);

        // create texture
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        // !! call SDL_FreeSurface passing in surface
        SDL_FreeSurface(surface);

        // check if texture was created
        if (m_texture == nullptr)
        {
            LOG(SDL_GetError());
            return false;
        }
        */
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

        // create texture
        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // !! call SDL_FreeSurface with surface as the parameter
        // !! no need to keep surface after texture is created
        SDL_FreeSurface(surface);

        return true;
    }

    Ethrl::Vector2 Texture::GetSize() const {
        //SDL_Point point;
        //SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);
        
        return Vector2{ 0, 0 };
    }
}

