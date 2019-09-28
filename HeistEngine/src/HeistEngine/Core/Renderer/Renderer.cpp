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

	void Renderer::Submit(const std::shared_ptr<Model3D>& model, const std::shared_ptr<Shader>& shader) {
		
		mat4 modelMatrix = MakeModelMatrix(model->position, model->rotation, model->scale);
		shader->UploadUniformMat4("modelMatrix", &modelMatrix);
		shader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // Once we get a command queue this can be done for each shader instead of model

		vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		HS_CORE_ASSERT(testModel.verticies.size() > 0, "No verticies passed in");
		vertexBuffer.reset(
			VertexBuffer::Create(testModel.verticies.data(), testModel.verticies.size() * sizeof(testModel.verticies[0]))
		);
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "Position" },
			});
		vertexBuffer->SetLayout(bufferLayout);

		std::shared_ptr<IndexBuffer> indexBuffer;
		HS_CORE_ASSERT(testModel.indicies.size() > 0, "No indicies passed in");
		indexBuffer.reset(
			IndexBuffer::Create(testModel.indicies.data(), testModel.indicies.size())
		);

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		RendererCommand::DrawIndexes(model->vertexArray);
	}
}