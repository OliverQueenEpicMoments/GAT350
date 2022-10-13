#include "Engine.h"
#include <iostream>

float Points[] = {
  -0.5f, -0.5f,  0.0f,
   -0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
   0.5f, 0.5f, 0, 
   0.5f, -0.5f, 0, 
   -0.5f, 0.5f, 0, 
};

glm::vec3 Colors[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{1, 1, 1}
};

glm::vec2 TexCoords[] = {
	{0, 0},
	{0, 1},
	{1, 0},
	{0, 1},
	{1, 1},
	{1, 0}
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

	// Create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), Points, GL_STATIC_DRAW);

	// Colors
	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), Colors, GL_STATIC_DRAW);

	// Textures
	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), TexCoords, GL_STATIC_DRAW);

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

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

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

	GLint Uniform1 = glGetUniformLocation(program, "scale");
	GLint Uniform2 = glGetUniformLocation(program, "tint");
	GLint Uniform3 = glGetUniformLocation(program, "transform");

	glUniform3f(Uniform2, 1, 1, 1);

	glm::mat4 mx{ 1 };
	//mx = glm::scale(glm::vec3{0.5, 0.5, 0.5});

	bool Quit = false;
	while (!Quit) {
		Ethrl::Engine::Instance().Update();
		if (Ethrl::g_inputSystem.GetKeyState(Ethrl::key_escape) == Ethrl::InputSystem::KeyState::Pressed) Quit = true;

		glUniform1f(Uniform1, std::sin(Ethrl::g_time.time));
		mx = glm::eulerAngleXYZ(0.0f, 0.0f, Ethrl::g_time.time);
		glUniformMatrix4fv(Uniform3, 1, GL_FALSE, glm::value_ptr(mx));

		Ethrl::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		Ethrl::g_renderer.EndFrame();
	}
	Ethrl::Engine::Instance().Shutdown();

	return 0;
}