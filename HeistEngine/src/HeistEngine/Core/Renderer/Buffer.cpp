#include "hspch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/Assertions.h"

#include "Platform/OpenGL/GLBuffer.h"

namespace Heist {

	VertexBuffer* VertexBuffer::Create(real32* vertices, uint32 size, uint32 count, bool staticDraw)
	{
		switch (Renderer::GetRenderAPI()) {
		case RenderAPI::API::OpenGL:
			return new GLVertexBuffer(vertices, size, count, staticDraw);
		case RenderAPI::API::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indicies, uint32 size, bool staticDraw)
	{
		switch (Renderer::GetRenderAPI()) {
		case RenderAPI::API::OpenGL:
			return new GLIndexBuffer(indicies, size, staticDraw);
		case RenderAPI::API::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

}