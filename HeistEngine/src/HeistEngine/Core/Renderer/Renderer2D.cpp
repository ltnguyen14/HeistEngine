#include "hspch.h"
#include "Renderer2D.h"
#include "VertexArray.h"

namespace Heist {

	struct Vertex2D {
		vec3 position;
		vec4 color;
	};

	Renderer2D::SceneData* Renderer2D::s_sceneData = new Renderer2D::SceneData;
	std::shared_ptr<VertexArray> Renderer2D::spriteVertexArray = nullptr;
	std::shared_ptr<VertexBuffer> Renderer2D::spriteVertexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> Renderer2D::spriteIndexBuffer = nullptr;
	std::shared_ptr<Shader> Renderer2D::spriteShader = nullptr;

	uint32 Renderer2D::quadCount = 0;

	void Renderer2D::ShutDown() {
		delete s_sceneData;
		// delete RendererCommand::s_renderAPI; // NOTE(LAM): 3D renderer is already deleting this. Will need to find a more robust way to handle this
	}

	void Renderer2D::Init() {
		const int32 BUFFER_QUAD_SIZE = 100000;
		const int32 IB_COUNT = BUFFER_QUAD_SIZE * 6;

		RendererCommand::Init();
		RendererCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1.0f });

		// VAO
		spriteVertexArray.reset(VertexArray::Create());

		// VBO
		spriteVertexBuffer.reset(VertexBuffer::Create(nullptr, BUFFER_QUAD_SIZE * sizeof(Vertex2D), false));
		BufferLayout bufferLayout({
			{ShaderDataType::Float3, "Position"},
			{ShaderDataType::Float4, "Color"},
		});
		spriteVertexBuffer->SetLayout(bufferLayout);

		// IBO
		int32 offset = 0;
		uint32 *indicies = new uint32[IB_COUNT]; // Size too large for stack
		for (uint32 i = 0; i < IB_COUNT; i += 6) {
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;

			indicies[i + 3] = offset + 2;
			indicies[i + 4] = offset + 3;
			indicies[i + 5] = offset + 0;

			offset += 4;
		}
		spriteIndexBuffer.reset(IndexBuffer::Create(indicies, IB_COUNT));
		delete[] indicies;

		// Assign VBO and IBO to VAO
		spriteVertexArray->AddVertexBuffer(spriteVertexBuffer);
		spriteVertexArray->SetIndexBuffer(spriteIndexBuffer);

		// Shaders
		spriteShader.reset(Shader::Create("assets/shaders/sprite.vert.glsl", "assets/shaders/sprite.frag.glsl"));
	}

	void Renderer2D::BeginScene(const std::shared_ptr<Camera>& camera) {
		HS_CORE_ASSERT(camera != nullptr, "Camera pointer is null");
		s_sceneData->projectionViewMatrix = camera->projectionViewMatrix;
	}

	void Renderer2D::EndScene() {
		spriteShader->Bind();
		spriteShader->UploadUniformMat4("modelMatrix", &mat4(1));
		spriteShader->UploadUniformMat4("projectionViewMatrix", &s_sceneData->projectionViewMatrix); // NOTE(LAM): Once we get a command queue this can be done for each shader instead of model

		RendererCommand::DrawIndexes(spriteVertexArray);
	}

	void Renderer2D::DrawSprite(const vec2 position, const vec2 scale, const vec4 color) {
		DrawSprite({ position.x, position.y, 0.0f }, scale, color);
	}

	void Renderer2D::DrawSprite(const vec3 position, const vec2 scale, const vec4 color) {
		real32 vertices[] = {
			position.x, position.y, position.z, color.r, color.g, color.b, color.a,
			position.x, position.y + scale.y, position.z, color.r, color.g, color.b, color.a,
			position.x + scale.x, position.y + scale.y, position.z, color.r, color.g, color.b, color.a,
			position.x + scale.x, position.y, position.z, color.r, color.g, color.b, color.a,
		};
		RendererCommand::VBOSubData(quadCount * sizeof(Vertex2D) * 4, sizeof(Vertex2D) * 4, vertices);
		quadCount++;
	}

	void Renderer2D::Flush() {
		
	}

}