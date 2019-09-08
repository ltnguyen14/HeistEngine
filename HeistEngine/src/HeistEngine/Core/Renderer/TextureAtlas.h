#pragma once
#include "Macro.h"

namespace Heist {

	struct TextureAtlas {

		virtual ~TextureAtlas() {};
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static TextureAtlas* Create(const char* texturePath);
	};

}