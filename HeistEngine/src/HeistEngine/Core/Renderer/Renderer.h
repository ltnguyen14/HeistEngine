#pragma once
#include "RendererCommand.h"
#include "Camera.h"
#include "Core/Math/Math.h"
#include "Model.h"
#include "Core/FileSystem/FileManager.h"

namespace Heist {

	struct Renderer {

		static void ShutDown();

		static void Init();
		static void BeginScene(const std::shared_ptr<Camera>& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<RawModel>& model);
		static void Submit(const std::shared_ptr<Model3D>& model, const std::shared_ptr<Shader>& shader);
		inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };
		
	private:
		struct SceneData {
			mat4 projectionViewMatrix;
		};

		static SceneData* s_sceneData;
	};

}