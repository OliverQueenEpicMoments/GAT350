#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace Ethrl
{
	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_enter = SDL_SCANCODE_RETURN;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;

	void InputSystem::Initialize()
	{
		int numKeys;
		// get pointer to sdl keyboard states and number of keys
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		// resize of keyboard state using numKeys for size
		m_keyboardState.resize(numKeys);

		// copy the sdl key states to keyboard state
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

		// set previous keyboard state to current keyboard state
		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		// get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		// mouse
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = Ethrl::Vector2{ (float)x , (float)y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]
	}

	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown)
		{
			keyState = (prevKeyDown) ? KeyState::Held : KeyState::Pressed;
		}
		else
		{
			keyState = (prevKeyDown) ? KeyState::Released : KeyState::Idle;
		}

		return keyState;
	}

	InputSystem::KeyState InputSystem::GetKeyState(const std::string& key)
	{
		//if (m_keyMap.find(key) != m_keyMap.end())
		//{
		//	return GetKeyState(m_keyMap[key]);
		//}

		return KeyState::Idle;
	}

	bool InputSystem::GetKeyDown(const std::string& key)
	{
		//if (m_keyMap.find(key) != m_keyMap.end())
		//{
		//	return m_keyboardState[m_keyMap[key]];
		//}
		
		return false;
	}

	bool InputSystem::GetPreviousKeyDown(const std::string& key)
	{
		//if (m_keyMap.find(key) != m_keyMap.end())
		//{
		//	return m_prevKeyboardState[m_keyMap[key]];
		//}

		return false;
	}


	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keyState = KeyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown)
		{
			keyState = (prevButtonDown) ? KeyState::Held : KeyState::Pressed;
		}
		else
		{
			keyState = (prevButtonDown) ? KeyState::Released : KeyState::Idle;
		}

		return keyState;
	}
}
