#include "CameraController.h"
#include "Engine.h"

namespace Ethrl {
    void CameraController::Initialize() {
        glm::vec3 v = math::QuaternionToEuler(m_owner->m_transform.rotation);
        m_pitch = v.x;
        m_yaw = v.y;
    }

    void CameraController::Update() {
        // get camera rotation
        if (g_inputSystem.GetButtonState(2) == InputSystem::KeyState::Held) {
            glm::vec2 axis = g_inputSystem.GetMouseRelative() * sensitivity;

            m_yaw += axis.x;
            m_pitch -= axis.y;
            m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
        }

        glm::quat qpitch = glm::angleAxis(glm::radians(m_pitch), glm::vec3{ 1, 0, 0 });
        glm::quat qyaw = glm::angleAxis(glm::radians(m_yaw), glm::vec3{ 0, 1, 0 });

        glm::quat q = qpitch * qyaw;
        glm::vec3 forward = q * glm::vec3{ 0, 0, 1 };

        glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f }, forward, glm::vec3{ 0, 1, 0 });
        m_owner->m_transform.rotation = glm::quat_cast(view);

        glm::vec3 direction{ 0 };

        if (g_inputSystem.GetKeyState(key_a) == InputSystem::KeyState::Held)	direction.x += 1;
        if (g_inputSystem.GetKeyState(key_d) == InputSystem::KeyState::Held)	direction.x -= 1;
        if (g_inputSystem.GetKeyState(key_q) == InputSystem::KeyState::Held)	direction.y += 1;
        if (g_inputSystem.GetKeyState(key_e) == InputSystem::KeyState::Held)	direction.y -= 1;
        if (g_inputSystem.GetKeyState(key_w) == InputSystem::KeyState::Held)	direction.z += 1;
        if (g_inputSystem.GetKeyState(key_s) == InputSystem::KeyState::Held)	direction.z -= 1;

        // convert world direction space to camera direction space
        direction = m_owner->m_transform.rotation * direction;
        m_owner->m_transform.position += direction * (speed * g_time.deltaTime);
    }

    bool CameraController::Write(const rapidjson::Value& value) const {
        return true;
    }

    bool CameraController::Read(const rapidjson::Value& value) {
        READ_DATA(value, speed);

        return true;
    }
}