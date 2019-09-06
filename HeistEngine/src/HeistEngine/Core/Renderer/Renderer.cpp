#include "hspch.h"
#include "Renderer.h"
#include "glad/glad.h"

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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		shader->Bind();
		vertexArray->Bind();

		int32 projMatrixLocation = glGetUniformLocation(shader->programId, "projectionViewMatrix");
		glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &s_sceneData->projectionViewMatrix[0][0]);

		RendererCommand::DrawIndexes(vertexArray);
	}
}