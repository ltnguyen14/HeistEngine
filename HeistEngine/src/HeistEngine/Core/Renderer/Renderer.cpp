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
		int32 textureSlot = 0;

		model->shader->Bind();
		model->vertexArray->Bind();

    if (model->material) {
      model->material->texture->Bind(textureSlot);
      model->material->specular->Bind(textureSlot + 1);
    }

		// Model
		model->shader->UploadUniformMat4("modelMatrix", &model->GetModelMatrix());

		model->shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model

		// Material
    if (model->material) {
      model->shader->UploadUniform1i("material.diffuse", textureSlot);
      model->shader->UploadUniform1i("material.specular", textureSlot + 1);
      model->shader->UploadUniform1f("material.reflectiveness", model->material->reflectiveness);
    } else if (model->rawMaterial) {
      model->shader->UploadUniformVec3("material.ambient", &model->rawMaterial->ambientColor);
      model->shader->UploadUniformVec3("material.diffuse", &model->rawMaterial->diffuseColor);
      model->shader->UploadUniformVec3("material.specular", &model->rawMaterial->specularColor);
      model->shader->UploadUniform1f("material.shininess", model->rawMaterial->shininess);
      model->shader->UploadUniform1i("material.specularHighlight", model->rawMaterial->specularHighlight);
    }

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
