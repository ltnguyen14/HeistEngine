#include "hspch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/Assertions.h"

#include "Platform/OpenGL/GLShader.h"

namespace Heist {

	Shader* Shader::Create(const char* vertexPath, const char* fragPath) {
		switch (Renderer::rendererAPI) {
		case RendererAPI::OpenGL:
			return new GLShader(vertexPath, fragPath);
		case RendererAPI::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

}