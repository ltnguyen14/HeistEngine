#pragma once
#include "Core/Renderer/Renderer.h"
#include "../BaseSystem.h"
#include "Core/Math/Math.h"
#include "Components.h"

namespace Heist {

	struct RenderSystem : public BaseSystem {
		RenderSystem() {}

		static void Update(real32 delta);
	};

}
