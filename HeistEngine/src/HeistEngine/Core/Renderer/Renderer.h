#pragma once
#include "RendererCommand.h"
#include "Shader.h"
#include "Core/Renderer/Camera.h"
#include "Core/Math/Math.h"

namespace Heist {

	struct Renderer {

		static void Init();
		static void BeginScene(const std::shared_ptr<Camera>& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };
		
	private:
		struct SceneData {
			mat4 projectionViewMatrix;
		};

		static SceneData* s_sceneData;
	};

}