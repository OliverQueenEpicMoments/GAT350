#include "VertexBuffer.h"

namespace Ethrl {
	VertexBuffer::VertexBuffer() {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
	}

	VertexBuffer::~VertexBuffer() {
	}

	bool Ethrl::VertexBuffer::Create(std::string name, ...) {
		return true;
	}

	void VertexBuffer::CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data) {
        m_vertexCount = vertexCount;

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetAttribute(int index, GLint size, GLsizei stride, size_t offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
	}

	void VertexBuffer::CreateIndexBuffer(GLenum indextype, GLsizei count, void* data) {
        m_indextype = indextype;
        m_indexcount = count;

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        size_t indexSize = (m_indextype == GL_UNSIGNED_SHORT) ? sizeof(GLushort) : sizeof(GLuint);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexcount * indexSize, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::Draw(GLenum primitiveType) {
        if (m_ibo) {
            glDrawElements(primitiveType, m_indexcount, m_indextype, 0);
        } else if (m_vbo) {
            glDrawArrays(primitiveType, 0, m_vertexCount);
        }
	}
}
