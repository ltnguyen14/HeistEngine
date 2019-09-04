#include "hspch.h"
#include "GLRenderAPI.h"
#include "glad/glad.h"

namespace Heist {
	void GLRenderAPI::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GLRenderAPI::SetClearColor(vec4 color){
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderAPI::ClearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderAPI::DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->indexBuffer->count, GL_UNSIGNED_INT, nullptr);
	}
}