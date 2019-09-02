#include "hspch.h"
#include "GLVertexArray.h"
#include "glad/glad.h"
#include "Platform/Assertions.h"

namespace Heist {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		HS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	GLVertexArray::GLVertexArray() {
		glCreateVertexArrays(1, &vao);
	}

	GLVertexArray::~GLVertexArray() {
		glDeleteVertexArrays(1, &vao);
	}

	void GLVertexArray::Bind() const {
		glBindVertexArray(vao);
	}

	void GLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void GLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		HS_CORE_ASSERT(vertexBuffer->layout.GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(vao);
		vertexBuffer->Bind();

		// Add layouts here
		const auto& layout = vertexBuffer->layout;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(vertexBufferIndex);
			glVertexAttribPointer(vertexBufferIndex,
				element.componentCount,
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.stride,
				(const void*)(intptr_t)element.offset);
			vertexBufferIndex++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void GLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(vao);
		indexBuffer->Bind();
		this->indexBuffer = indexBuffer;
	}

}