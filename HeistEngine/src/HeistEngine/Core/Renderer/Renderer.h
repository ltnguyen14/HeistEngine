#pragma once

namespace Heist {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1
	};

	struct Renderer {

		static RendererAPI rendererAPI;

	};

}