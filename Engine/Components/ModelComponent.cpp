#include "ModelComponent.h"
#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace Ethrl {
	void ModelComponent::Update() {
		//
	}

	void ModelComponent::Draw(Renderer& renderer) {
        material->Bind();

        // Set MVP matrix for model
        material->GetProgram()->SetUniform("model", (glm::mat4)m_owner->m_transform);
        material->GetProgram()->SetUniform("view", renderer.GetView());
        material->GetProgram()->SetUniform("projection", renderer.GetProjection());

        model->m_vertexbuffer.Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const {
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value) {
        // Read model name
		std::string model_name;
		READ_DATA(value, model_name);

        // Get model from model name
		model = g_resources.Get<Model>(model_name);
        
        // Read material name
        std::string material_name;
        READ_DATA(value, material_name);

        // Get material from material name
        material = g_resources.Get<Material>(material_name);

		return true;
	}
}
