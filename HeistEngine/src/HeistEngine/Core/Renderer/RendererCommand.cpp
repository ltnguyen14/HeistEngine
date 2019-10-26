#include "hspch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/GLRenderAPI.h"

namespace Heist {

#ifdef RENDERER_OPENGL
	RenderAPI* RendererCommand::s_renderAPI = new GLRenderAPI;
#else
#error Render API not supported
#endif

}