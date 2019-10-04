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

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera, Light3D *light) {
		HS_CORE_ASSERT(camera != nullptr, "Camera pointer is null");
		s_sceneData->projectionViewMatrix = camera->projectionViewMatrix;
		s_sceneData->light = light;
		s_sceneData->camera = camera;
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Model3D>& model) {
		model->shader->Bind();
		model->vertexArray->Bind();
		model->texture->Bind();

		// Model
		model->shader->UploadUniformMat4("modelMatrix", &model->GetModelMatrix());
		model->shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model

		// Material
		model->shader->UploadUniformVec3("material.ambient", &model->material->ambient);
		model->shader->UploadUniformVec3("material.diffuse", &model->material->diffuse);
		model->shader->UploadUniformVec3("material.specular", &model->material->specular);
		model->shader->UploadUniform1f("material.reflectiveness", model->material->reflectiveness);

		// Light
		model->shader->UploadUniformVec3("light.position", &s_sceneData->light->position);
		model->shader->UploadUniformVec3("light.ambient", &s_sceneData->light->ambient);
		model->shader->UploadUniformVec3("light.diffuse", &s_sceneData->light->diffuse);
		model->shader->UploadUniformVec3("light.specular", &s_sceneData->light->specular);


		if (model->useIndicies) {
			RendererCommand::DrawIndexes(model->vertexArray);
		} else {
			RendererCommand::DrawVerticies(model->vertexArray);
		}

	}
}