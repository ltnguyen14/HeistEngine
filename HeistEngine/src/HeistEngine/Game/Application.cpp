#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title) 
		: window(&eventBus, width, height, title) {
		running = true;
	}

	Application::~Application() {}

	void Application::OnUpdate() {
		window.OnUpdate();
	}

	void Application::OnEvent() {}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer) {
		layerStack.PopLayer(layer);
	}

	void Application::Run() {
		while (!window.ShouldClose()) {
			window.ClearWindow();
			this->OnUpdate();
			eventBus.Notify();
		};
	}
}