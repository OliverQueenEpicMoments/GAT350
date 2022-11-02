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

        // Get program resource
        m_program = Ethrl::g_resources.Get<Ethrl::Program>(program);

        // Read the texture name 
        std::string texture;
        READ_DATA(document, texture);
        if (!texture.empty()) {
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

        for (auto& texture : m_textures) {
            texture->Bind();
        }
    }
}