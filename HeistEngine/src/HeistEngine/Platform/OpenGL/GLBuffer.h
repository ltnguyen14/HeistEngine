#pragma once
#include "Core/Renderer/Buffer.h"

namespace Heist {

	struct GLVertexBuffer : public VertexBuffer {
		GLVertexBuffer(real32* vertices, uint32 size, bool staticDraw);
		~GLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void SetLayout(BufferLayout& layout) override;	
	};

	struct GLIndexBuffer : public IndexBuffer {
		GLIndexBuffer(uint32* indicies, uint32 count, bool staticDraw);
		~GLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
	};

}