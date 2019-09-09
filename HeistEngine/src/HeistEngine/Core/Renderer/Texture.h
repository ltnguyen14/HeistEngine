#pragma once
#include "Macro.h"

namespace Heist {

	struct Texture {

		virtual ~Texture() {};
		
		virtual void Bind(int32 textureSlot = 0) = 0;
		virtual void Unbind() = 0;

		static Texture* Create(const char* texturePath);

		uint32 textureId;
		int32 width, height;
		int32 comp;
	};

}