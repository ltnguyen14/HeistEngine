#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"
#include "Core/Renderer/Renderer.h"

#include "glad/glad.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title) 
		: window(&eventBus, width, height, title), memoryManager(2) {
		running = true;

		shader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));

		// ----------------- Rendering
		real32 verticies[] = {
			 1.0f,  1.0f, 0.0f, 0.2f, 0.4f, 0.8f, 1.0f,
			 1.0f,  0.0f, 0.0f, 0.8f, 0.4f, 0.2f, 1.0f,
			 0.0f,  0.0f, 0.0f, 0.4f, 0.4f, 0.4f, 1.0f,
			 0.0f,  1.0f, 0.0f, 0.4f, 0.4f, 0.8f, 1.0f 
		};
		uint32 indicies[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		
		vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float4, "Color" },
		});
		vertexBuffer->SetLayout(bufferLayout);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indicies, 6));

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		camera.reset(new Camera({ 0, 0, 0 }, { 0, 0, 0 }, {0, 10.8, 0, 7.2 }));
	}

	Application::~Application() {}

	void Application::OnUpdate(real64 time) {
	}

	void Application::OnRender() {
		window.ClearWindow();
		// Render stuff go here

		Renderer::BeginScene(camera);

		static real32 x = 0;
		static real32 y = 0;
		x += 0.00001;
		y += 0.00001;
		mat4 modelMatrix = mat4(1).translate({x, y, 0});

		int32 projMatrixLocation = glGetUniformLocation(shader->programId, "modelMatrix");
		glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

		Renderer::Submit(shader, vertexArray);

		Renderer::EndScene();

		// --------------------
		window.SwapBuffer();
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer) {
		layerStack.PopLayer(layer);
	}

	void Application::Run() {
		// Main loop setup
		real64 lag = 0.0f;
		real64 targetFPS = 60.0f;
		real64 MS_PER_UPDATE = 1000.0f / targetFPS;
		clock_t previous = clock();
		real32 frameTime = 0.0f;
		const int32 MAX_FRAME_SKIP = 10;
		int32 loops = 0;

		while (!window.ShouldClose()) {
			// Time stuff
			clock_t current = clock();
			auto elapsed = current - previous;

			previous = current;
			lag += elapsed;
			// ------

			// Update
			window.PollEvents();

			loops = 0;
			while (lag >= MS_PER_UPDATE && loops < MAX_FRAME_SKIP) {
				this->OnUpdate(MS_PER_UPDATE);
				lag -= MS_PER_UPDATE;
				loops++;
			}

			// Render
			this->OnRender();
			eventBus.Notify(); // TODO(LAM): Need to move this somewhere
			frameTime = float(clock() - current);
		};
	}
}