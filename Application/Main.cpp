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

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";

const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 0.1, 0.0, 1.0);"
"}";

int main(int argc, char** argv) {
	Ethrl::InitializeMemory();

	Ethrl::Engine::Instance().Initialize();
	Ethrl::Engine::Instance().Register();

	Ethrl::g_renderer.CreateWindow("Neumont", 800, 600);

	// Create vertex buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), Points, GL_STATIC_DRAW);

	// Create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// Create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
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