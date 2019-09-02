#include "hspch.h"
#include "GLBuffer.h"
#include "glad/glad.h"

namespace Heist {

	GLVertexBuffer::GLVertexBuffer(real32* vertices, uint32 size) {
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer() {
		glDeleteBuffers(1, &vbo);
	}

	void GLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void GLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLVertexBuffer::SetLayout(BufferLayout& layout) {
		this->layout = layout;
	}

	// ----------------------------------------------------------------------------

	GLIndexBuffer::GLIndexBuffer(uint32* indicies, uint32 count) {
		this->count = count;
		glCreateBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indicies, GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer() {
		glDeleteBuffers(1, &ebo);
	}

	void GLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	}

	void GLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

