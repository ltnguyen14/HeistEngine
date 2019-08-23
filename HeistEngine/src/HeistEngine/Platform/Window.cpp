#include "hspch.h"
#include "Window.h"

namespace Heist {
	Window::Window(EventBus *eventBus) : EventNode(eventBus, "Window"){};
	Window::~Window() {};
}