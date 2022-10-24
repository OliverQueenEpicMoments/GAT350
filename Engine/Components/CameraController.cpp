#include "CameraController.h"
#include "Engine.h"

namespace Ethrl {
    void CameraController::Update() {
        // Update transform
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_left) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x -= speed * g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_right) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x += speed * g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_up) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y += speed * g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_down) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y -= speed * g_time.deltaTime;
    }

    bool CameraController::Write(const rapidjson::Value& value) const {
        return true;
    }

    bool CameraController::Read(const rapidjson::Value& value) {
        READ_DATA(value, speed);

        return true;
    }
}