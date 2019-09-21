#pragma once
#include "Core/Renderer/RenderAPI.h"

namespace Heist {

	struct GLRenderAPI : public RenderAPI {

		void Init() override;
		void SetClearColor(vec4 color) override;
		void ClearScreen() override;

		void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) override;
		void VBOSubData(uint32 offsetBytes, uint32 sizeBytes, real32* data) override;

	};

}