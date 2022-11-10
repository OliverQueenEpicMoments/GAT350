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
    Ethrl::g_gui.Initialize(Ethrl::g_renderer);

    // Load scene
    auto Scene = Ethrl::g_resources.Get<Ethrl::Scene>("Scenes/Texture.snc");

    glm::vec3 Position = { 0, 0, 0 };
    float X = 0;
    float Y = 0;
    float Z = 0;
	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
        Ethrl::g_gui.BeginFrame(Ethrl::g_renderer);

		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

        auto Actor = Scene->GetActorFromName("Heisenbones");
        if (Actor) {
            //Actor->m_transform.rotation.y += Ethrl::g_time.deltaTime * 90.0f;
        }

        auto Light = Scene->GetActorFromName("Light");
        if (Light) {
            // move light using sliders
            Light->m_transform.position = Position;
        }

        ImGui::Begin("Hello");
        ImGui::SliderFloat3("Light Position", &Position[0], -5, 5);
        ImGui::End();

        Scene->Update();

		Ethrl::g_renderer.BeginFrame();

        Scene->Draw(Ethrl::g_renderer);
        Ethrl::g_gui.Draw();

		Ethrl::g_renderer.EndFrame();
        Ethrl::g_gui.EndFrame();
	}

    Scene->RemoveAll();
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}