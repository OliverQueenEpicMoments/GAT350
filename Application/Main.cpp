#include "Engine.h"
#include <iostream>

#define POST_PROCESS

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

    // Create Framebuffer Texture
    auto Texture = std::make_shared<Ethrl::Texture>();
    Texture->CreateTexture(1024, 1024);
    Ethrl::g_resources.Add<Ethrl::Texture>("FB_Texture", Texture);

    // Create Framebuffer
    auto Framebuffer = Ethrl::g_resources.Get<Ethrl::Framebuffer>("Framebuffer", "FB_Texture");
    Framebuffer->Unbind();

    // Load scene
    auto Scene = Ethrl::g_resources.Get<Ethrl::Scene>("Scenes/RTT.snc");

    glm::vec3 Rotation = { 0, 0, 0 };
    glm::vec3 Position = { 0, 2, -5 };
    glm::vec3 Position2 = { 3, 2, 4 };
    glm::vec3 Position3 = { -1.5f, 2, 4 };
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

        auto Light3 = Scene->GetActorFromName("Light3");
        if (Light3) {
            // move light using sliders
            Light3->m_transform.position = Position3;
        }

        auto program = Ethrl::g_resources.Get<Ethrl::Program>("Shaders/FX/Reflect_Refract.prog");
        if (program) {
            program->Use();
            program->SetUniform("ri", ri);
            program->SetUniform("interp", interp);
        }

        auto Program2 = Ethrl::g_resources.Get<Ethrl::Program>("Shaders/PostProcess/postprocess.prog");
        if (Program2) {
            Program2->Use();
            Program2->SetUniform("offset", Ethrl::g_time.time);
        }

        ImGui::Begin("Everything");
        ImGui::DragFloat3("Rotation", &Rotation[0]);
        ImGui::DragFloat3("Light Position", &Position[0]);
        ImGui::DragFloat3("Light2 Position", &Position2[0]);
        ImGui::DragFloat3("Light3 Position", &Position3[0]);
        ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 4);
        ImGui::DragFloat("Interpolation", &interp, 0.01f, 0, 10);
        ImGui::End();

        Scene->Update();

#ifdef POST_PROCESS

        // Don't draw post process actor when rendering to the framebuffer
        {
            auto actor = Scene->GetActorFromName("PostProcess");
            if (actor) {
                actor->SetActive(false);
            }
        }

        // Render pass 1 (Render to Framebuffer)
        Ethrl::g_renderer.SetViewport(0, 0, Framebuffer->GetSize().x, Framebuffer->GetSize().y);
        Framebuffer->Bind();

		Ethrl::g_renderer.BeginFrame();

        Scene->PreRender(Ethrl::g_renderer);
        Scene->Render(Ethrl::g_renderer);
        Framebuffer->Unbind();

        // Render pass 2 (Render to screen)
        Ethrl::g_renderer.RestoreViewport();
        Ethrl::g_renderer.BeginFrame();
        Scene->PreRender(Ethrl::g_renderer);

        // Draw only the post process actor to the screen
        {
            auto actor = Scene->GetActorFromName("PostProcess");
            if (actor) {
                actor->SetActive(true);
                actor->Draw(Ethrl::g_renderer);
            }
        }

#else

        Ethrl::g_renderer.BeginFrame();
        Scene->PreRender(Ethrl::g_renderer);
        Scene->Render(Ethrl::g_renderer);

#endif

        Ethrl::g_gui.Draw();

		Ethrl::g_renderer.EndFrame();
        Ethrl::g_gui.EndFrame();
	}

    Scene->RemoveAll();
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}