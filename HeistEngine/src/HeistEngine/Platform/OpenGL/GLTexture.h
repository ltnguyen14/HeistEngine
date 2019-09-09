#pragma once
#include "Core/Renderer/Texture.h"

namespace Heist {

	struct GLTexture : Texture {

		GLTexture(const char* texturePath);
		~GLTexture();

		void Bind(int32 textureSlot = 0);
		void Unbind();

	};

}