#pragma once
#include "Core/Renderer/TextureAtlas.h"

namespace Heist {

	struct GLTexture : TextureAtlas {

		GLTexture(const char* texturePath);
		~GLTexture();

		void Bind();
		void Unbind();

	};

}