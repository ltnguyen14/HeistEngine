#pragma once
#include "Core/Renderer/VertexArray.h"

namespace Heist {

	struct GLVertexArray : public VertexArray {

		GLVertexArray();
		~GLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		uint32 vertexBufferIndex = 0;
	};

}