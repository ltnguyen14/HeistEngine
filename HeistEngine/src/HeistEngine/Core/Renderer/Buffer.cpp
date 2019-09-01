#include "hspch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/Assertions.h"

#include "Platform/OpenGL/GLBuffer.h"

namespace Heist {

	VertexBuffer* VertexBuffer::Create(real32* vertices, uint32 size)
	{
		switch (Renderer::rendererAPI) {
		case RendererAPI::OpenGL:
			return new GLVertexBuffer(vertices, size);
		case RendererAPI::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indicies, uint32 size)
	{
		switch (Renderer::rendererAPI) {
		case RendererAPI::OpenGL:
			return new GLIndexBuffer(indicies, size);
		case RendererAPI::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

}