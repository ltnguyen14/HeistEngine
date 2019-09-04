#include "hspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/GLVertexArray.h"

namespace Heist {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetRenderAPI()) {
		case RenderAPI::API::OpenGL:
			return new GLVertexArray();
		case RenderAPI::API::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}
}