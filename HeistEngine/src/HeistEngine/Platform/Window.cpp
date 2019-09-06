#include "hspch.h"
#include "Window.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"

namespace Heist {
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		HS_CORE_INFO(std::to_string(key) + " was pressed!");
	}

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
		glfwSetWindowUserPointer(window, this);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);

		// Set key callbacks
		glfwSetKeyCallback(window, key_callback);
	};

	Window::~Window() {
		glfwTerminate();
	}

	void Window::SwapBuffer() {
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	void Window::PollEvents() {
		/* Poll for and process events */
		glfwPollEvents();
	}

	void Window::OnNotify(Event event) {
	}
}