#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace Ethrl {
    class Texture;

    class Framebuffer : public Resource {
    public:
        ~Framebuffer();

        bool Create(std::string filename, ...) override;
        bool CreateFramebuffer();
        bool CreateDepthbuffer(int width, int height);

        void Bind();
        void Unbind();

        glm::ivec2 GetSize() const { return { m_width, m_height }; }

    protected:
        GLuint m_fbo = 0;
        std::shared_ptr<Texture> m_texture;

        int m_width = 0;
        int m_height = 0;
    };
}