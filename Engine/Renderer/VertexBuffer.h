#pragma once
#include "Renderer.h"
#include "Resource\Resource.h"
#include <vector>

namespace Ethrl {
	class VertexBuffer : public Resource {
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		bool Create(std::string name, ...) override;

		// Vertex Buffer
		void CreateVertexBuffer(GLsizei size, GLsizei m_vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

        // Index Buffer
        void CreateIndexBuffer(GLenum indextype, GLsizei count, void* data);

		virtual void Draw(GLenum primitiveType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(m_vao); }

	protected:
		GLuint m_vao = 0; // vertex array object

		GLuint m_vbo = 0; // vertex buffer object
		GLuint m_vertexCount = 0; // number of vertices in vertex buffer

        GLuint m_ibo = 0; // Index buffer object
        GLuint m_indexcount = 0; // Number of indices in index buffer
        GLenum m_indextype = 0; // Data type of index
	};
}