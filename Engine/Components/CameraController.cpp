#include "CameraController.h"
#include "Engine.h"

namespace Ethrl {
    void CameraController::Update() {
        // Update transform
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_left) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x -= speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_right) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x += speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_up) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y += speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_down) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y -= speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_s) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.z += speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_w) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.z -= speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_a) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x -= speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_d) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.x += speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_e) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y += speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_q) == Ethrl::InputSystem::KeyState::Held) m_owner->m_transform.position.y -= speed * Ethrl::g_time.deltaTime;
    }

    bool CameraController::Write(const rapidjson::Value& value) const {
        return true;
    }

    bool CameraController::Read(const rapidjson::Value& value) {
        READ_DATA(value, speed);

        return true;
    }
}