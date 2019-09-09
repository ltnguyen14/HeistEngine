#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"
#include "Core/Renderer/Renderer.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title) 
		: window(&eventBus, width, height, title), memoryManager(20) {
		running = true;

		Renderer::Init();
		shader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));
		// ----------------- Rendering
		real32 verticies[] = {
			// front				   
			0.0, 0.0, 0.0,		0.0, 0.0,
			1.0, 0.0, 0.0,		1.0, 0.0,
			1.0, 1.0, 0.0,		1.0, 1.0,
			0.0, 1.0, 0.0,		0.0, 1.0,
			// back					 	  
			0.0, 0.0, 0.0,		0.0, 0.0,
			1.0, 0.0, 0.0,		1.0, 0.0,
			1.0, 1.0, 0.0,		1.0, 1.0,
			0.0, 1.0, 0.0,		0.0, 1.0,
		};
		uint32 indicies[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};
		
		vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float2, "Texture Coords" },
		});
		vertexBuffer->SetLayout(bufferLayout);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indicies, 6));

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		camera.reset(new Camera({ 0, 0, 0 }, { 0, 0, 0 }, {0, 10.8, 7.2, 0 }));

		textureAtlas.reset(Texture::Create("assets/textures/texture.png"));
	}

	Application::~Application() {}

	void Application::OnUpdate(real64 time) {
	}

	void Application::OnRender() {
		// Render stuff go here

		Renderer::BeginScene(camera);

		mat4 modelMatrix = mat4(1).translate({ 1.0f, 1.0f, 0.0f });

		std::shared_ptr<RawModel> model(new RawModel(shader, textureAtlas, vertexArray, &modelMatrix));
		Renderer::Submit(model);

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