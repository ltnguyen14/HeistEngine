#include "hspch.h"
#include "TextureAtlas.h"
#include "Renderer.h"
#include "Platform/Assertions.h"

#include "Platform/OpenGL/GLTexture.h"

namespace Heist {

	TextureAtlas* TextureAtlas::Create(const char* texturePath)
	{
		switch (Renderer::GetRenderAPI()) {
		case RenderAPI::API::OpenGL:
			return new GLTexture(texturePath);
		case RenderAPI::API::None:
			return nullptr;
		}

		HS_CORE_ERROR("RendereAPI unknown!");
		return nullptr;
	}

}