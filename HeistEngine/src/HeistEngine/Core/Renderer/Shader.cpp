#include "hspch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/Assertions.h"

#include "Platform/OpenGL/GLShader.h"

namespace Heist {

	Shader* Shader::Create(const char* vertexPath, const char* fragPath) {
		switch (Renderer::GetRenderAPI()) {
		case RenderAPI::API::OpenGL:
			return new GLShader(vertexPath, fragPath);
		case RenderAPI::API::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

}