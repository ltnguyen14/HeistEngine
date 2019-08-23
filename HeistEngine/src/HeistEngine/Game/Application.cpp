#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Assertions.h"

namespace Heist {

	Application::Application() : window(&eventBus) {
		running = true;
	}

	Application::~Application() {}

	void Application::OnUpdate() {
		window.OnUpdate();
	}

	void Application::OnEvent() {}

	void Application::Run() {
		while (running) {
			this->OnUpdate();
		};
	}
}