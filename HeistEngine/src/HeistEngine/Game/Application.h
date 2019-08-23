#pragma once
#include "../Macro.h"
#include "Platform/Window.h"
#include "Core/Event/EventBus.h"

namespace Heist {
	class Application {
	public:
		Application();
		virtual ~Application();

		void OnUpdate();
		void OnEvent();

		void Run();

	private:
		bool running;
		EventBus eventBus;
		Window window;
	};
	
	// To be defined in client
	Application* CreateApplication();
}