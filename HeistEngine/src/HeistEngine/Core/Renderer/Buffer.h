#pragma once
#include "Macro.h"

namespace Heist {

	struct VertexBuffer {
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

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