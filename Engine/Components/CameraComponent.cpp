#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace Ethrl {
    void CameraComponent::Update() {
        m_view = glm::lookAt(m_owner->m_transform.position, m_owner->m_transform.position + m_owner->m_transform.GetForward(), glm::vec3{ 0, 1, 0 });
    }

    void CameraComponent::SetPerspective(float fov, float aspectratio, float near, float far) {
        m_projection = glm::perspective(glm::radians(fov), aspectratio, near, far);
    }

    void CameraComponent::SetProgram(std::shared_ptr<Program> program) {
        program->Use();
        program->SetUniform("view", m_view);
        program->SetUniform("projection", m_projection);
    }

    bool CameraComponent::Write(const rapidjson::Value& value) const {
        return true;
    }

    bool CameraComponent::Read(const rapidjson::Value& value) {
        float fov;
        READ_DATA(value, fov);
        float aspect_ratio;
        if (!READ_DATA(value, aspect_ratio)) {
            aspect_ratio = g_renderer.GetWidth() / (float(g_renderer.GetHeight()));
        }

        float near;
        READ_DATA(value, near);
        float far;
        READ_DATA(value, far);

        SetPerspective(fov, aspect_ratio, near, far);

        return true;
    }
}
