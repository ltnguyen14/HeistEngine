#include "hspch.h"
#include "Renderer.h"

namespace Heist {

	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::ShutDown() {
		delete s_sceneData;
		delete RendererCommand::s_renderAPI;
	}

	void Renderer::Init() {
		RendererCommand::Init();
		RendererCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1.0f });
	}

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera) {
		HS_CORE_ASSERT(camera != nullptr, "Camera pointer is null");
		s_sceneData->projectionViewMatrix = camera->projectionViewMatrix;
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<RawModel>& model) {
		model->shader->Bind();
		model->vertexArray->Bind();
		model->texture->Bind();

		model->shader->UploadUniformMat4("modelMatrix", model->modelMatrix);
		model->shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model

		RendererCommand::DrawIndexes(model->vertexArray);
	}
}