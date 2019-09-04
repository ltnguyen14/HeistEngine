#include "hspch.h"
#include "Renderer.h"

namespace Heist {
	void Renderer::Init() {
		RendererCommand::Init();
	}

	void Renderer::BeginScene() {
		RendererCommand::ClearScreen();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		shader->Bind();
		vertexArray->Bind();
		RendererCommand::DrawIndexes(vertexArray);
	}
}