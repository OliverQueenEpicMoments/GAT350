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
        READ_DATA(document, ambient);
        READ_DATA(document, diffuse);
        READ_DATA(document, specular);
        READ_DATA(document, shininess);

        return true;
    }

    void Material::Bind() {
        m_program->Use();
        for (auto& texture : m_textures) {
            texture->Bind();
        }
    }
}