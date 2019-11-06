#pragma once
#include "RendererCommand.h"
#include "Camera.h"
#include "Core/Math/Math.h"
#include "Shader.h"
#include "Texture.h"

namespace Heist {

	struct Vertex2D {
		vec3 position;
		vec4 color;
	};

  struct TextVertex2D {
    vec3 position;
    vec2 textureCoords;
    vec4 color;
  };

	struct Renderer2D {

		static void ShutDown();

		static void Init();
		static void BeginScene(const std::shared_ptr<Camera>& camera);
    static void LoadFontTexture(const std::shared_ptr<Texture>& fontTexture);
		static void EndScene();

		static void DrawSprite(const vec2& position, const vec2& scale, const vec4& color);
		static void DrawSprite(const vec3& position, const vec2& scale, const vec4& color);
    static void DrawText(const vec4& rect, const vec4& textureCoords, const vec4& color);

		static void Flush();
    static void FlushText();

		inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };

	private:
		struct SceneData {
			mat4 projectionViewMatrix;
		};

		static SceneData* s_sceneData;
		static std::shared_ptr<VertexArray> spriteVertexArray;
		static std::shared_ptr<VertexBuffer> spriteVertexBuffer;
		static std::shared_ptr<IndexBuffer> spriteIndexBuffer;
		static std::shared_ptr<Shader> spriteShader;
		static real32* vertices;
		static uint32 quadCount;

		static std::shared_ptr<VertexArray> textVertexArray;
		static std::shared_ptr<VertexBuffer> textVertexBuffer;
		static std::shared_ptr<IndexBuffer> textIndexBuffer;
		static std::shared_ptr<Shader> textShader;
    static real32* textVerticies;
    static uint32 textQuadCount;
    static std::shared_ptr<Texture> fontTexture;

		static const int32 BUFFER_QUAD_SIZE = 100000;
		static const int32 IB_COUNT = BUFFER_QUAD_SIZE * 6;

	};
}
