#include "Engine.h"
#include <iostream>

int main() {
	Ethrl::InitializeMemory();

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();

		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

		Ethrl::g_renderer.BeginFrame();
		Ethrl::g_renderer.EndFrame();
	}
	Ethrl::Engine::Instance().Shutdown();
}