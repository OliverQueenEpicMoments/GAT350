#include "LightComponent.h"
#include "Engine.h"

namespace Ethrl {
	void LightComponent::Update() {
        //
	}

	void LightComponent::SetProgram(std::shared_ptr<Program> program, int index) {
        // Transform the light position by the view, puts light in model view space
        glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->m_transform.position, 1);
        glm::vec3 direction = m_owner->m_transform.GetForward();

        // Create array light name 
        std::string lightname = "lights[" + std::to_string(index) + "]";

        // set programs light properties
        program->Use();
        program->SetUniform(lightname + ".type", (int)type);
        program->SetUniform(lightname + ".color", color);
        program->SetUniform(lightname + ".position", position);
        program->SetUniform(lightname + ".direction", direction);
        program->SetUniform(lightname + ".cutoff", glm::radians(cutoff));
        program->SetUniform(lightname + ".exponent", exponent);
	}

	bool LightComponent::Write(const rapidjson::Value& value) const {
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value) {
        READ_DATA(value, color);
        READ_DATA(value, cutoff);
        READ_DATA(value, exponent);

        std::string type_name;
		READ_DATA(value, type_name);
        if (CompareIgnoreCase(type_name, "directional")) {
            type = Type::Directional;
        } else if (CompareIgnoreCase(type_name, "spot")) {
            type = Type::Spot;
        } else {
            type = Type::Point;
        }
		return true;
	}
}