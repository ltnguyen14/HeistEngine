#include "hspch.h"
#include "Window.h"
#include "Core/Log.h"

namespace Heist {
	Window::Window(EventBus *eventBus, int32 width, int32 height, std::string title) 
		: EventNode(eventBus, "Window"), width(width), height(height), title(title) {

		/* Initialize the library */
		if (!glfwInit())
			HS_CORE_ERROR("Error initializing GLFW!");

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			HS_CORE_ERROR("Error initializing window!");
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);
	};

	Window::~Window() {
		glfwTerminate();
	}

	void Window::OnUpdate() {

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	void Window::OnNotify(Event event) {
	}
}