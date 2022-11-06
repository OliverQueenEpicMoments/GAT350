#include "Engine.h"
#include <iostream>

int main(int argc, char** argv) {
	LOG("Application started...");
	Ethrl::InitializeMemory();
	Ethrl::SetFilePath("../Assets");

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();
	LOG("Engine Initialized...");

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");

    // Load scene
    auto Scene = Ethrl::g_resources.Get<Ethrl::Scene>("Scenes/Texture.snc");

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

        auto Ogre = Scene->GetActorFromName("Ogre");
        if (Ogre) {
            //Ogre->m_transform.rotation.y += Ethrl::g_time.deltaTime * 90.0f;
        }

        auto Light = Scene->GetActorFromName("Light");
        if (Light) {
            // move light using sin wave
            Light->m_transform.position.y = std::sin(Ethrl::g_time.time);
        }

        auto Material = Ethrl::g_resources.Get<Ethrl::Material>("Materials/Multi.mtrl");
        if (Material) {
            //Material->uv_offset += glm::vec2(Ethrl::g_time.deltaTime);
        }

        Scene->Update();

		Ethrl::g_renderer.BeginFrame();

        Scene->Draw(Ethrl::g_renderer);

		Ethrl::g_renderer.EndFrame();
	}
    Scene->RemoveAll();
	Ethrl::Engine::Instance().Shutdown();

	return 0; // 38 minutes in the zoom
}