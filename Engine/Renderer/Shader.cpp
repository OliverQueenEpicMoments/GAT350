#include "Shader.h"
#include <Core/Logger.h>
#include <Core/File.h>

namespace Ethrl {
	Shader::~Shader() {
		if (m_Shader != 0) {
			glDeleteShader(m_Shader);
		}
	}

	bool Shader::Create(std::string filename, ...) {
		// get shader source from file
		std::string source;
		bool success = ReadFile(filename, source);
		if (!success) {
			LOG("Error reading shader file %s.", filename.c_str());
			return false;
		}

		// get shader type arguments
		va_list args;
		va_start(args, filename);
		GLuint shaderType = va_arg(args, GLuint);
		va_end(args);

		// create shader
		m_Shader = glCreateShader(shaderType);

		// compile shader
		const char* source_c = source.c_str();
		glShaderSource(m_Shader, 1, &source_c, NULL);
		glCompileShader(m_Shader);

		// check shader compilation status
		GLint status;
		glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			// display shader error
			GLint length = 0;
			glGetShaderiv(m_Shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0) {
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(m_Shader, length, &length, &infoLog[0]);
				LOG("Failed to compile shader %s.", filename.c_str());
				LOG("Shader info: %s", infoLog.c_str());
			}

			// delete shader
			glDeleteShader(m_Shader);
			m_Shader = 0;
		}
		return true;
	}
}