#pragma once
#include "RendererCommand.h"
#include "Shader.h"

namespace Heist {

	struct Renderer {

		static void Init();
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };

	};

}