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
    float ri = 1;
    float interp = 1;
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

        auto program = Ethrl::g_resources.Get<Ethrl::Program>("Shaders/FX/Reflect_Refract.prog");
        if (program) {
            program->Use();
            program->SetUniform("ri", ri);
            program->SetUniform("interp", interp);
        }

        ImGui::Begin("Everything");
        ImGui::DragFloat3("Rotation", &Rotation[0]);
        ImGui::DragFloat3("Light Position", &Position[0]);
        ImGui::DragFloat3("Light2 Position", &Position2[0]);
        ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 4);
        ImGui::DragFloat("Interpolation", &interp, 0.01f, 0, 10);
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