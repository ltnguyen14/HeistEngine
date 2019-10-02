#include "hspch.h"
#include "Renderer.h"

namespace Heist {

	SceneData* Renderer::s_sceneData = new SceneData;

	void Renderer::ShutDown() {
		delete s_sceneData;
		delete RendererCommand::s_renderAPI;
	}

	void Renderer::Init() {
		RendererCommand::Init();
		RendererCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1.0f });
	}

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera, vec3 lightPosition, vec3 lightColor) {
		HS_CORE_ASSERT(camera != nullptr, "Camera pointer is null");
		s_sceneData->projectionViewMatrix = camera->projectionViewMatrix;
		s_sceneData->lightPosition = lightPosition;
		s_sceneData->camera = camera;
		s_sceneData->lightColor = lightColor;
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<RawModelData>& model) {
		model->shader->Bind();
		model->vertexArray->Bind();
		model->texture->Bind();

		model->shader->UploadUniformMat4("modelMatrix", model->modelMatrix);
		model->shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model
		model->shader->UploadUniformVec3("lightPosition", &s_sceneData->lightPosition);
		model->shader->UploadUniformVec3("viewPosition", &s_sceneData->camera->position);
		model->shader->UploadUniformVec3("lightColor", &s_sceneData->lightColor);

		RendererCommand::DrawIndexes(model->vertexArray);
	}

	void Renderer::Submit(const std::shared_ptr<Model3D>& model) {
		model->shader->Bind();
		model->vertexArray->Bind();
		model->texture->Bind();

		model->shader->UploadUniformMat4("modelMatrix", &model->GetModelMatrix());
		model->shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model
		model->shader->UploadUniformVec3("lightPosition", &s_sceneData->lightPosition);
		model->shader->UploadUniformVec3("lightColor", &s_sceneData->lightColor);

		if (model->useIndicies) {
			RendererCommand::DrawIndexes(model->vertexArray);
		} else {
			RendererCommand::DrawVerticies(model->vertexArray);
		}

	}
}