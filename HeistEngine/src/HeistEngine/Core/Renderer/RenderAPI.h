#pragma once
#include "Core/Renderer/VertexArray.h"
#include "Core/Math/Math.h"

namespace Heist {

	class RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetClearColor(vec4 color) = 0;
		virtual void ClearScreen() = 0;

		virtual void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void VBOSubData(uint32 offsetBytes, uint32 sizeBytes, real32* data) = 0;

		inline static API GetAPI() { return s_API; }
	private:	
		static API s_API;
	};
}