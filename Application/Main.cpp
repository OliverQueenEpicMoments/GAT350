#include "Engine.h"
#include <iostream>

float Points[] = {
  -0.5, -0.5f,  0.0f,
   -0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
   0.5f, 0.5f, 0, 
   0.5f, -0.5f, 0, 
   -0.5f, 0.5f, 0, 
};

Ethrl::Vector3 Colors[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{1, 1, 1}
};

int main(int argc, char** argv) {
	Ethrl::InitializeMemory();
	Ethrl::SetFilePath("../Assets");

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);

	// Create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), Points, GL_STATIC_DRAW);

	// Colors
	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Ethrl::Vector3), Colors, GL_STATIC_DRAW);

	// Create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create shader
	std::shared_ptr<Ethrl::Shader> vs = Ethrl::g_resources.Get<Ethrl::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<Ethrl::Shader> fs = Ethrl::g_resources.Get<Ethrl::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

	/*GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);*/

	// Create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_Shader);
	glAttachShader(program, vs->m_Shader);
	glLinkProgram(program);
	glUseProgram(program);

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

		Ethrl::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		Ethrl::g_renderer.EndFrame();
	}
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}