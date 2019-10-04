#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"

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

		camera.reset(new Camera({ 0, 0, 0 }, { 0, 0, 0 }, {0, 1080, 720, 0 }, false));

		textureAtlas.reset(Texture::Create("assets/textures/woodBox.png"));
		textureSpecAtlas.reset(Texture::Create("assets/textures/woodBox_spec.png"));

		shader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));
		sunShader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/sun.frag.glsl"));

		// Material 
		material.reset(new Material3D(
			textureAtlas,
			textureSpecAtlas,
			64.0f));

		// Test loading model
		auto rawModel = FileManager::ReadOBJFile("assets/models/cube_texture.obj");
		testModel.reset(FileManager::CreateModelFromRawData(&rawModel, material, shader, textureAtlas));
		testModel->position = { 0, 0, 5 };

		sunModel = FileManager::ReadOBJFile("assets/models/sphere.obj");
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
		// camera->position.x += 4.0f;
		camera->Update();

		if (window.resize) {
			camera->UpdateDimension({ 0, (real32)window.width, (real32)window.height, 0 });
			window.resize = false;
		}

		// Basic camera movement - Please remove
		if (inputManager->GetKey(HS_KEY_Q)) {
			camera->position.y += 0.2f;
 		}
		if (inputManager->GetKey(HS_KEY_E)) {
			camera->position.y -= 0.2f;
		}

		if (inputManager->GetKey(HS_KEY_W)) {
			camera->position.z += 0.2f;
		}
		if (inputManager->GetKey(HS_KEY_S)) {
			camera->position.z -= 0.2f;
		}

		if (inputManager->GetKey(HS_KEY_A)) {
			camera->position.x -= 0.2f;
		}
		if (inputManager->GetKey(HS_KEY_D)) {
			camera->position.x += 0.2f;
		}

		if (inputManager->GetKey(HS_KEY_Z)) {
			camera->rotation.y += 2.0f;
		}
		if (inputManager->GetKey(HS_KEY_X)) {
			camera->rotation.y -= 2.0f;
		}

		// --------------------------------------

		testModel->rotation.y += 0.3f;

		memoryManager->ClearStack();
	}

	void Application::OnRender() {
		// Render stuff go here
		RendererCommand::ClearScreen();

		// Test loading models
		vec3 lightPosition = { -5, 0, -2 };

		Light3D light(lightPosition, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f });

		std::shared_ptr<Model3D> testModel2(FileManager::CreateModelFromRawData(&sunModel, material, sunShader, textureAtlas));
		testModel2->position = lightPosition;

		Renderer::BeginScene(camera, &light);

		Renderer::Submit(testModel);
		Renderer::Submit(testModel2);

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

				// Render
				this->OnRender();
				loops++;
			}

			frameTime = float(clock() - current);
		};
	}
}