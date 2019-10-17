#include "hspch.h"
#include "Application.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title)
		: window(width, height, title) {
		running = true;

		//Subsystem start up
		memoryManager = MemoryManager::Instance();
		memoryManager->StartUp(10);
		window.StartUp();
		inputManager = InputManager::Instance();
		inputManager->StartUp();

		// Event Bus Subscription
		window.SubscribeToBus(&eventBus);
		inputManager->SubscribeToBus(&eventBus);

		// Camera init
		camera = std::make_shared<Heist::Camera>(Heist::vec3(0, 0, 0), Heist::vec3(0, 0, 0), Heist::vec4(0, width, height, 0), false);

		// --------------------
		Renderer::Init();
		Renderer2D::Init();

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

    if (cameraMovement) {
      cameraMovement->Update();
    }
		camera->Update();
		if (window.resize) {
			camera->UpdateDimension({ 0, (real32)window.width, (real32)window.height, 0 });
			for (auto layer : layerStack.layers) {
				layer->OnWindowResize(0, (real32)window.width, (real32)window.height, 0);
			}
			window.resize = false;
		}

		for (auto layer : layerStack.layers) {
			layer->OnUpdate(time);
		}
		memoryManager->ClearStack();
	}

	void Application::OnRender() {
		// Render stuff go here
		RendererCommand::ClearScreen();

		for (auto layer : layerStack.layers) {
			layer->OnRender(camera);
		}
		window.SwapBuffer();
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer) {
		layerStack.PopLayer(layer);
	}

  void Application::AttachCameraMovement(CameraMovement *movement) {
    cameraMovement = movement;
	  movement->camera = camera.get();
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
