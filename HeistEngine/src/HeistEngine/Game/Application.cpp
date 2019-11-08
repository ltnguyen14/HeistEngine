#include "hspch.h"
#include "Application.h"
#include "Game/ECS/Common/Systems.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title)
		: window(width, height, title) {
		running = true;

		//Subsystem start up
		memoryManager = MemoryManager::Instance();
		memoryManager->StartUp(100);
		window.StartUp();
		inputManager = InputManager::Instance();
		inputManager->StartUp();
    guiManager = GUIManager::Instance();
    guiManager->StartUp();
		componentManager = std::make_shared<ComponentManager>(ComponentManager());
		BaseSystem::RegisterComponentManager(componentManager);

		// Event Bus Subscription
		window.SubscribeToBus(&eventBus);
		inputManager->SubscribeToBus(&eventBus);

		// Camera init
		camera = std::make_shared<Heist::Camera>(Heist::vec3(0, 0, 0), Heist::vec3(0, 0, 0), Heist::vec4(0, width, height, 0), false);
		orthoCamera = std::make_shared<Heist::Camera>(Heist::vec3(0, 0, 0), Heist::vec3(0, 0, 0), Heist::vec4(0, width, height, 0), true);

		// --------------------
		Renderer::Init();
		Renderer2D::Init();
    GUIManager::SetupFont("assets/fonts/RobotoMedium.png", "assets/fonts/RobotoMedium.fnt");
	}

	Application::~Application() {
		window.ShutDown();
		inputManager->ShutDown();
		memoryManager->ShutDown();
    guiManager->ShutDown();
		Renderer::ShutDown();

		for (auto layer : layerStack.layers) {
			delete layer;
		}
	}

	void Application::OnUpdate(real64 time) {

		if (cameraMovement) {
			cameraMovement->Update();
		}
		camera->Update();
		if (window.resize) {
			camera->UpdateDimension({ 0, (real32)window.width, (real32)window.height, 0 });
			orthoCamera->UpdateDimension({ 0, (real32)window.width, (real32)window.height, 0 });
			for (auto layer : layerStack.layers) {
				layer->OnWindowResize(0, (real32)window.width, (real32)window.height, 0);
			}
			window.resize = false;
		}

		for (auto layer : layerStack.layers) {
			layer->OnUpdate(time);
		}

		inputManager->ResetScroll();
		eventBus.Notify(); // TODO(LAM): Need to move this somewhere
		memoryManager->ClearStack();
	}

	void Application::OnRender(real64 time) {
		// Render stuff go here
		RendererCommand::ClearScreen();

		for (auto layer : layerStack.layers) {
			Renderer::BeginScene(camera, &layer->light);
			layer->OnRender(camera);
			RenderSystem::Update(time);
			Renderer::EndScene();

			Renderer2D::BeginScene(orthoCamera);
      GUIManager::BeginFrame();
			layer->OnOverlay();
      GUIManager::EndFrame();
			Renderer2D::EndScene();

			// Stats
			GUIManager::BeginFrame();
			static int32 i = 0;
			static real32 cachedTime = time;
			i++;
			if (i % 60 == 0) {
				Heist::GUIManager::Text(std::to_string((int32)time), { 0.0f, 0.0f, 64.0f, 64.0f }, { 0.2f, 0.4f, 0.33f, 1.0f }, 0.5f);
				cachedTime = time;
				i = 1;
			}
			else {
				Heist::GUIManager::Text(std::to_string((int32)cachedTime), { 0.0f, 0.0f, 64.0f, 64.0f }, { 0.2f, 0.4f, 0.33f, 1.0f }, 0.5f);
			}
			GUIManager::EndFrame();
		}

		window.SwapBuffer();
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer, componentManager);
	}

	void Application::PopLayer(Layer* layer) {
		layerStack.PopLayer(layer);
	}

	void Application::AttachCameraMovement(CameraMovement* movement) {
		movement->AttachCamera(camera.get());
		cameraMovement = movement;
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

		while (!window.ShouldClose() && running) {
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
				this->OnUpdate(MS_PER_UPDATE / 1000);

				loops++;
				lag -= MS_PER_UPDATE;
        // HS_CORE_INFO("{}", frameTime);
			}

      // Render
      this->OnRender(frameTime);

			frameTime = float(clock() - current);
			// HS_CORE_INFO("{} ms", frameTime);
		};
	}
}
