#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"

#include "Core/FileSystem/FileManager.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title) 
		: window(width, height, title) {
		running = true;

		//Subsystem start up
		memoryManager = MemoryManager::Instance();
		memoryManager->StartUp(500);
		window.StartUp();
		inputManager = InputManager::Instance();
		inputManager->StartUp();

		// Event Bus Subscription
		window.SubscribeToBus(&eventBus);
		inputManager->SubscribeToBus(&eventBus);

		// --------------------
		Renderer::Init();
		Renderer2D::Init();

#if 0
		shader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));
		// ----------------- Rendering
		real32 verticies[] = {
			// front				   
			-0.5, -0.5,	 0.5,		0.0, 0.0,
			 0.5, -0.5,  0.5,		1.0, 0.0,
			 0.5,  0.5,  0.5,		1.0, 1.0,
			-0.5,  0.5,  0.5,		0.0, 1.0,
			// right				   
			 0.5, -0.5,	 0.5,		0.0, 0.0,
			 0.5, -0.5, -0.5,		1.0, 0.0,
			 0.5,  0.5, -0.5,		1.0, 1.0,
			 0.5,  0.5,  0.5,		0.0, 1.0,
			// back					 	  
			-0.5, -0.5, -0.5,		0.0, 0.0,
			 0.5, -0.5, -0.5,		1.0, 0.0,
			 0.5,  0.5, -0.5,		1.0, 1.0,
			-0.5,  0.5, -0.5,		0.0, 1.0,
			// left				   
			-0.5, -0.5,	-0.5,		0.0, 0.0,
			-0.5, -0.5,  0.5,		1.0, 0.0,
			-0.5,  0.5,  0.5,		1.0, 1.0,
			-0.5,  0.5, -0.5,		0.0, 1.0,
			// top				   
			-0.5,  0.5,	 0.5,		0.0, 0.0,
			 0.5,  0.5,  0.5,		1.0, 0.0,
			 0.5,  0.5, -0.5,		1.0, 1.0,
			-0.5,  0.5, -0.5,		0.0, 1.0,
			// bottom				   
			-0.5, -0.5,	-0.5,		0.0, 0.0,
			 0.5, -0.5, -0.5,		1.0, 0.0,
			 0.5, -0.5,  0.5,		1.0, 1.0,
			-0.5, -0.5,  0.5,		0.0, 1.0,

		};
		uint32 indicies[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			4, 5, 6,
			6, 7, 4,
			// back
			8, 9, 10,
			10, 11, 8,
			// left
			12, 13, 14,
			14, 15, 12,
			// top
			16, 17, 18,
			18, 19, 16,
			// bottom
			20, 21, 22,
			22, 23, 20
		};
		
		// ------------------ First cube
		vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float2, "Texture Coords" },
		});
		vertexBuffer->SetLayout(bufferLayout);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indicies, 6 * 6));

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		// ---------------------- Second cube
		vertexArray2.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer2;
		vertexBuffer2.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		BufferLayout bufferLayout2({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float2, "Texture Coords" },
			});
		vertexBuffer2->SetLayout(bufferLayout2);

		std::shared_ptr<IndexBuffer> indexBuffer2;
		indexBuffer2.reset(IndexBuffer::Create(indicies, 6 * 6));

		vertexArray2->AddVertexBuffer(vertexBuffer2);
		vertexArray2->SetIndexBuffer(indexBuffer2);

		// ----------------

		// ---------------------- Third cube
		vertexArray3.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer3;
		vertexBuffer3.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		BufferLayout bufferLayout3({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float2, "Texture Coords" },
			});
		vertexBuffer3->SetLayout(bufferLayout3);

		std::shared_ptr<IndexBuffer> indexBuffer3;
		indexBuffer3.reset(IndexBuffer::Create(indicies, 6 * 6));

		vertexArray3->AddVertexBuffer(vertexBuffer3);
		vertexArray3->SetIndexBuffer(indexBuffer3);

		// ----------------
#endif
		camera.reset(new Camera({ 0, 0, 0 }, { 0, 0, 0 }, {0, 1080, 720, 0 }, true));

		textureAtlas.reset(Texture::Create("assets/textures/texture.png"));
	}

	Application::~Application() {
		window.ShutDown();
		inputManager->ShutDown();
		memoryManager->ShutDown();
		Renderer::ShutDown();

		delete inputManager;
		delete memoryManager;
		for (auto layer : layerStack.layers) {
			delete layer;
		}
	}

	void Application::OnUpdate(real64 time) {
		eventBus.Notify(); // TODO(LAM): Need to move this somewhere
		camera->position.x += 4.0f;
		camera->Update();

		memoryManager->ClearStack();
	}

	void Application::OnRender() {
		// Render stuff go here
		RendererCommand::ClearScreen();

#if 0
		Renderer::BeginScene(camera);

		static real32 rot = 0.0f;
		rot += 0.01f;
		mat4 modelMatrix = MakeModelMatrix({ 0, 0, 5 }, { rot, 0, 0 }, {1, 1, 1});
		mat4 modelMatrix2 = MakeModelMatrix({ 2, 0, 5 }, { 0, rot, 0 }, { 1, 1, 1 });
		mat4 modelMatrix3 = MakeModelMatrix({ -2, 0, 5 }, { 0, 0, rot }, { 1, 1, 1 });

		std::shared_ptr<RawModel> model(new RawModel(shader, textureAtlas, vertexArray, &modelMatrix));
		std::shared_ptr<RawModel> model2(new RawModel(shader, textureAtlas, vertexArray2, &modelMatrix2));
		std::shared_ptr<RawModel> model3(new RawModel(shader, textureAtlas, vertexArray3, &modelMatrix3));

		Renderer::Submit(model);
		Renderer::Submit(model2);
		Renderer::Submit(model3);

		Renderer::EndScene();
#endif

		Renderer2D::BeginScene(camera);
		for (int32 y = 0; y < 250; y++) {
			for (int32 x = 0; x < 250; x++) {
				Renderer2D::DrawSprite({ x * 33.0f, y * 33.0f }, { 32.0f, 32.0f }, { 0.2f, 0.4f, 0.8f, 1.0f });
			}
		}
		Renderer2D::EndScene();
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
			frameTime = float(clock() - current);
			HS_CORE_INFO("Time: {}ms, FPS: {}", frameTime, 1000/frameTime);
		};
	}
}