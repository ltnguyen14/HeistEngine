#pragma once
#include "RendererCommand.h"
#include "Camera.h"
#include "Core/Math/Math.h"
#include "Model.h"
#include "Core/FileSystem/FileManager.h"

namespace Heist {

	struct SceneData {
		std::shared_ptr<Camera> camera;
		mat4 projectionViewMatrix;
		vec3 lightPosition;
		vec3 lightColor;
	};

	struct Renderer {
		static void ShutDown();

		static void Init();
		static void BeginScene(const std::shared_ptr<Camera>& camera, vec3 lightPosition, vec3 lightColor);
		static void EndScene();

		static void Submit(const std::shared_ptr<RawModelData>& model);
		static void Submit(const std::shared_ptr<Model3D>& model);

		inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };
		
	private:
		static SceneData* s_sceneData;
	};

}