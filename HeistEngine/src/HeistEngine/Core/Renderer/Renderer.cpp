#include "hspch.h"
#include "Renderer.h"

namespace Heist {

	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::Init() {
		RendererCommand::Init();
	}

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera) {
		HS_CORE_ASSERT(camera != nullptr, "Camera pointer is null");
		RendererCommand::ClearScreen();
		s_sceneData->projectionViewMatrix = camera->projectionViewMatrix;
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const mat4* modelMatrix) {
		shader->Bind();
		vertexArray->Bind();

		shader->UploadUniformMat4("modelMatrix", modelMatrix);
		shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix);

		RendererCommand::DrawIndexes(vertexArray);
	}
}