#pragma once
#include "Macro.h"
#include "Platform/Assertions.h"

namespace Heist {

	// Buffer layout stuff -------------------------------------
	// ---------------------------------------------------------
	enum class ShaderDataType {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32 ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 8;
		case ShaderDataType::Float3:	return 12;
		case ShaderDataType::Float4:	return 16;
		case ShaderDataType::Mat3:		return 36;
		case ShaderDataType::Mat4:		return 64;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 8;
		case ShaderDataType::Int3:		return 12;
		case ShaderDataType::Int4:		return 16;
		case ShaderDataType::Bool:		return 1;
		}

		HS_CORE_ASSERT(false, "Unknown data type!");
		return 0;
	}

	struct BufferElement {
		BufferElement(ShaderDataType type, const std::string& name)
			:name(name), type(type), size(ShaderDataTypeSize(type)), offset(0) {};

		BufferElement() {};

		std::string name;
		ShaderDataType type;
		uint32 offset;
		uint32 size;
	};

	struct BufferLayout {
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:elements(elements), stride(0) {
			CalculateOffsetAndStride();
		};

		BufferLayout() {};

		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement> elements;
		uint32 stride;

	private:
		void CalculateOffsetAndStride() {
			uint32 offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	};

	// -----------------------------------------------------

	struct VertexBuffer {
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(BufferLayout& layout) = 0;

		static VertexBuffer* Create(real32* vertices, uint32 size);

		uint32 vbo;
	};

	struct IndexBuffer {
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(uint32* indicies, uint32 size);

		uint32 ebo, count;
	};
}