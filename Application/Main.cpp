#include "Engine.h"
#include <iostream>

float Vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv) {
	LOG("Application started...");
	Ethrl::InitializeMemory();
	Ethrl::SetFilePath("../Assets");

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();
	LOG("Engine Initialized...");

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");

    // Create Vertex Buffer
    std::shared_ptr<Ethrl::VertexBuffer> VB = Ethrl::g_resources.Get<Ethrl::VertexBuffer>("Box");
    VB->CreateVertexBuffer(sizeof(Vertices), 36, Vertices);
    VB->SetAttribute(0, 3, 8 * sizeof(float), 0);
    VB->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    VB->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Create Material
    std::shared_ptr<Ethrl::Material> material = Ethrl::g_resources.Get<Ethrl::Material>("Materials/Box.txt");
    material->Bind();

    material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
    material->GetProgram()->SetUniform("scale", 0.5f);

	glm::mat4 Model{ 1 };
    glm::mat4 Projection = glm::perspective(45.0f, Ethrl::g_renderer.GetWidth() / (float)Ethrl::g_renderer.GetHeight(), 0.01f, 100.0f);

    glm::vec3 CameraPosition(0, 0, 1);
    float Speed = 3;

    std::vector<Ethrl::Transform> Transforms;
    for (size_t I = 0; I < 15; I++) {
        Transforms.push_back({ { Ethrl::randomf(-2, 5), Ethrl::randomf(-2, 5), Ethrl::randomf(-2, 5)}, {0, Ethrl::random(360), 0} });
    }

    auto M = Ethrl::g_resources.Get<Ethrl::Model>("Models/Ogre.obj");

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

        // Move the camera
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_left) == Ethrl::InputSystem::KeyState::Held) CameraPosition.x -= Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_right) == Ethrl::InputSystem::KeyState::Held) CameraPosition.x += Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_up) == Ethrl::InputSystem::KeyState::Held) CameraPosition.y += Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_down) == Ethrl::InputSystem::KeyState::Held) CameraPosition.y -= Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_s) == Ethrl::InputSystem::KeyState::Held) CameraPosition.z += Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_w) == Ethrl::InputSystem::KeyState::Held) CameraPosition.z -= Speed * Ethrl::g_time.deltaTime;

        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_a) == Ethrl::InputSystem::KeyState::Held) CameraPosition.x -= Speed * Ethrl::g_time.deltaTime;
        if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_d) == Ethrl::InputSystem::KeyState::Held) CameraPosition.x += Speed * Ethrl::g_time.deltaTime;

        glm::mat4 View = glm::lookAt(CameraPosition, CameraPosition + glm::vec3(0, 0, -1), glm::vec3( 0, 1, 0 ));

		//Model = glm::eulerAngleXYZ(0.0f, Ethrl::g_time.time, 0.0f);
        //material->GetProgram()->SetUniform("scale", std::sin(Ethrl::g_time.time * 3)); Bounces box.

		Ethrl::g_renderer.BeginFrame();

        for (size_t I = 0; I < Transforms.size(); I++) {
            Transforms[I].rotation += glm::vec3{ 0, 90 * Ethrl::g_time.deltaTime, 0 };

            glm::mat4 MVP = Projection * View * (glm::mat4)Transforms[I];
            material->GetProgram()->SetUniform("MVP", MVP);

            VB->Draw();
            M->m_vertexbuffer.Draw();
        }

		Ethrl::g_renderer.EndFrame();
	}
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}