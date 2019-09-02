#include "hspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/GLVertexArray.h"

namespace Heist {

	VertexArray* VertexArray::Create() {
		switch (Renderer::rendererAPI) {
		case RendererAPI::OpenGL:
			return new GLVertexArray();
		case RendererAPI::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}
}