#include "hspch.h"
#include "GLRenderAPI.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Heist {
	void GLRenderAPI::Init() {
		// GLAD init
		HS_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to init GLAD");
	}

	void GLRenderAPI::SetClearColor(vec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderAPI::SetBlend(bool value) {
		if (value) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			glDisable(GL_BLEND);
		}
	}

	void GLRenderAPI::SetDepthTest(bool value) {
		if (value) {
			glEnable(GL_DEPTH_TEST);
		} else {
			glDisable(GL_DEPTH_TEST);
		}
	}

	void GLRenderAPI::ClearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderAPI::DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->indexBuffer->count, GL_UNSIGNED_INT, nullptr);
	}

	void GLRenderAPI::DrawVerticies(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->vertexBuffers[0]->count);
	}

	void GLRenderAPI::VBOSubData(uint32 offsetBytes, uint32 sizeBytes, real32* data) {
		glBufferSubData(GL_ARRAY_BUFFER, offsetBytes, sizeBytes, data);
	}
}
