#include "hspch.h"
#include "Renderer.h"

namespace Heist {

#ifdef RENDERER_OPENGL
	RendererAPI Renderer::rendererAPI = RendererAPI::OpenGL;
#else
	RendererAPI Renderer::rendererAPI = None;
#endif
}