#include "Material.h"
#include "Engine.h"

namespace Ethrl {
    bool Material::Create(std::string FileName, ...) {
        // load program JSON file
        rapidjson::Document document;
        bool success = Ethrl::json::Load(FileName, document);
        if (!success) {
            LOG("Could not load program file (%s).", FileName.c_str());
            return false;
        }

        // Read the program name
        std::string program;
        READ_DATA(document, program);

        // read cube map
        std::string cubemap;
        READ_DATA(document, cubemap);
        if (!cubemap.empty()) {
            std::string cubemap_extension;
            READ_DATA(document, cubemap_extension);
            m_textures.push_back(Ethrl ::g_resources.Get<Ethrl::CubemapTexture>(cubemap, cubemap_extension));
        }

        // Get program resource
        m_program = Ethrl::g_resources.Get<Ethrl::Program>(program);

        // Read the texture name 
        std::vector<std::string> textures;
        READ_DATA(document, textures);
        for (auto texture : textures) {
            // Get texture resource
            m_textures.push_back(Ethrl::g_resources.Get<Ethrl::Texture>(texture));  
        }

        // Read Colors
        READ_DATA(document, color);
        READ_DATA(document, shininess);

        // Read uvs
        READ_DATA(document, uv_tiling);
        READ_DATA(document, uv_offset);

        return true;
    }

    void Material::Bind() {
        m_program->Use();
        m_program->SetUniform("material.color", color);
        m_program->SetUniform("material.shininess", shininess);
        m_program->SetUniform("material.uv_tiling", uv_tiling);
        m_program->SetUniform("material.uv_offset", uv_offset);

        for (size_t I = 0; I < m_textures.size(); I++) {
            m_textures[I]->SetActive(GL_TEXTURE0 + (int)I);
            m_textures[I]->Bind();
        }
    }
}