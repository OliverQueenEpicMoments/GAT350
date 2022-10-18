#include "Program.h"
#include "Engine.h"

namespace Ethrl {
    Program::~Program() {
        if (m_program) {
            glDeleteProgram(m_program);
        }
    }

    bool Program::Create(std::string FileName, ...) {
        // Load program json document
        rapidjson::Document document;
        bool Success = Ethrl::json::Load(FileName, document);
        if (!Success) {
            LOG("Could not load file (%s).", FileName.c_str());
            return false;
        }
        
        // Create Program
        m_program = glCreateProgram();

        // Get/Add vertex shader
        std::string vertex_shader;
        READ_DATA(document, vertex_shader);
        if (!vertex_shader.empty()) {
            auto vshader = g_resources.Get<Ethrl::Shader>(vertex_shader, GL_VERTEX_SHADER);
            AddShader(vshader);
        }

        // Get/Add fragment shader
        std::string fragment_shader;
        READ_DATA(document, fragment_shader);
        if (!fragment_shader.empty()) {
            auto fshader = g_resources.Get<Ethrl::Shader>(fragment_shader, (void*)GL_FRAGMENT_SHADER);
            AddShader(fshader);
        }

        Link();

        return true;
    }

    void Program::AddShader(const std::shared_ptr<Shader>& Shader) {
        m_shaders.push_back(Shader);

        glAttachShader(m_program, Shader->m_Shader);
    }

    void Program::Link() {
        // Link shader programs
        glLinkProgram(m_program);

        // Chack program link status
        GLint status;
        glGetProgramiv(m_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);

            if (length > 0) {
                std::string infoLog(length, ' ');

                glGetProgramInfoLog(m_program, length, &length, &infoLog[0]);

                LOG("Failed to link program.");
                LOG("Program Info: %s", infoLog.c_str());
            }
            glDeleteProgram(m_program);
            m_program = 0;
        }
    }

    void Program::Use() {
        glUseProgram(m_program);
    }

    void Program::SetUniform(const std::string& Name, float Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform1f(uniform, Value);
    }

    void Program::SetUniform(const std::string& Name, const glm::vec3& Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform3fv(uniform, 1, &Value[0]);
    }

    void Program::SetUniform(const std::string& Name, const glm::mat4& Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(Value));
    }

    // The rest of these SetUniforms might not work properly

    void Program::SetUniform(const std::string& Name, int Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform1i(uniform, Value);
    }

    void Program::SetUniform(const std::string& Name, unsigned int Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform1ui(uniform, Value);
    }

    void Program::SetUniform(const std::string& Name, bool Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform1i(uniform, Value);
;    }

    void Program::SetUniform(const std::string& Name, const glm::vec2& Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform2fv(uniform, 1, &Value[0]);
    }

    void Program::SetUniform(const std::string& Name, const glm::vec4& Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniform4fv(uniform, 1, &Value[0]);
    }

    void Program::SetUniform(const std::string& Name, const glm::mat3& Value) {
        GLint uniform = GetUniform(Name);
        if (uniform != -1) glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(Value));
    }

    GLint Program::GetUniform(const std::string& Name) {
        // Find uniform in map 
        auto uniform = m_uniforms.find(Name);

        // If not found, get uniform in program
        if (uniform == m_uniforms.end()) {
            // Get uniform in program
            GLint location = glGetUniformLocation(m_program, Name.c_str());
            if (location == -1) {
                LOG("Could not find uniform location: %s", Name.c_str());
            }
            m_uniforms[Name] = location;
        }

        return m_uniforms[Name];
    }
}