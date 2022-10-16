#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"
#include "Math/MathUtils.h"
#include <map>
#include <vector>

namespace Ethrl {
	class Shader;

	class Program : public Resource {
	public:
		~Program();

		virtual bool Create(std::string FileName, ...) override;
		void AddShader(const std::shared_ptr<Shader>& Shader);

		void Link();
		void Use();

		// Uniforms
		void SetUniform(const std::string& Name, float Value);
		void SetUniform(const std::string& Name, const glm::vec3& Value);
		void SetUniform(const std::string& Name, const glm::mat4& Value);

		void SetUniform(const std::string& Name, int Value);
		void SetUniform(const std::string& Name, unsigned int Value);
		void SetUniform(const std::string& Name, bool Nalue);

		void SetUniform(const std::string& Name, const glm::vec2& Value);
		void SetUniform(const std::string& Name, const glm::vec4& Value);

		void SetUniform(const std::string& Name, const glm::mat3& Value);

	private:
		GLint GetUniform(const std::string& Name);

	public:
		GLuint m_program = 0;
		std::vector<std::shared_ptr<Shader>> m_shaders;
		std::map<std::string, GLint> m_uniforms;
	};
}