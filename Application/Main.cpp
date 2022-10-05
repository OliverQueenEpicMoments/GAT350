#include "Engine.h"
#include <iostream>

int main(int argc, char** argv) {
	Ethrl::InitializeMemory();

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();

		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

		Ethrl::g_renderer.BeginFrame();

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		Ethrl::g_renderer.EndFrame();
	}
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}