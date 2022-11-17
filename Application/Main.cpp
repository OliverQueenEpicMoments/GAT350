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
    auto Scene = Ethrl::g_resources.Get<Ethrl::Scene>("Scenes/Cubemap.snc");

    glm::vec3 Rotation = { 0, 0, 0 };
    glm::vec3 Position = { 0, 0, 0 };
    glm::vec3 Position2 = { 0, 0, 0 };
	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
        Ethrl::g_gui.BeginFrame(Ethrl::g_renderer);

		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

        auto Actor = Scene->GetActorFromName("Heisenbones");
        if (Actor) {
            Actor->m_transform.rotation = math::EulerToQuaternion(Rotation);
        }

        auto Light = Scene->GetActorFromName("Light");
        if (Light) {
            // move light using sliders
            Light->m_transform.position = Position;
        }

        auto Light2 = Scene->GetActorFromName("Light2");
        if (Light2) {
            // move light using sliders
            Light2->m_transform.position = Position2;
        }

        ImGui::Begin("Bruh");
        ImGui::SliderFloat3("Rotation", &Rotation[0], -360, 360);
        ImGui::End();

        ImGui::Begin("Brah");
        ImGui::SliderFloat3("Light Position", &Position[0], -5, 5);
        ImGui::End();

        ImGui::Begin("Breh");
        ImGui::SliderFloat3("Light2 Position", &Position2[0], -5, 5);
        ImGui::End();

        Scene->Update();

		Ethrl::g_renderer.BeginFrame();

        Scene->PreRender(Ethrl::g_renderer);
        Scene->Render(Ethrl::g_renderer);
        Ethrl::g_gui.Draw();

		Ethrl::g_renderer.EndFrame();
        Ethrl::g_gui.EndFrame();
	}

    Scene->RemoveAll();
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}