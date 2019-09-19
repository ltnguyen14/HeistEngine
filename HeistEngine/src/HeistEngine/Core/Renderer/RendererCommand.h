#pragma once
#include "RenderAPI.h"

namespace Heist {

	struct RendererCommand {

		inline static void Init() {
			s_renderAPI->Init();
		}

		inline static void SetClearColor(vec4 color) {
			s_renderAPI->SetClearColor(color);
		}

		inline static void ClearScreen() {
			s_renderAPI->ClearScreen();
		}

		inline static void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) {
			s_renderAPI->DrawIndexes(vertexArray);
		}

		inline static void VBOSubData(uint32 offsetBytes, real32 *data) {
			s_renderAPI->VBOSubData(offsetBytes, data);
		}

		static RenderAPI* s_renderAPI;
	};
}