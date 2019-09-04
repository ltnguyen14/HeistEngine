#include "hspch.h"
#include "RenderAPI.h"

namespace Heist {
#ifdef RENDERER_OPENGL
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
#else
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::None;
#endif
}