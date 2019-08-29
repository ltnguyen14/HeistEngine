#include "hspch.h"
#include "Window.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"
#include "glad/glad.h"

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

		// GLAD init
		int gladInit = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		HS_CORE_ASSERT(gladInit, "Failed to init GLAD");

		// OpenGl clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

	void Window::ClearWindow() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::OnNotify(Event event) {
	}
}