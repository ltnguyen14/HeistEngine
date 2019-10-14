#include "hspch.h"
#include "Window.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"
#include "glad/glad.h"

namespace Heist {
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		KeyEvent* event = (KeyEvent*)win->g_memoryManager->Alloc(sizeof(KeyEvent));
		new(event) KeyEvent(key, action);

		win->SendEvent(event);
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->width = width;
		win->height = height;
		win->resize = true;
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}

	Window::Window(int32 width, int32 height, std::string title) 
		: EventNode("Window"), width(width), height(height), title(title) {

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
		glfwSetWindowSizeCallback(window, window_size_callback);

		g_memoryManager = MemoryManager::Instance();
	};

	Window::~Window() {
		glfwTerminate();
	}

	void Window::StartUp() {

	}

	void Window::ShutDown() {

	}

	void Window::SwapBuffer() {
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	void Window::PollEvents() {
		/* Poll for and process events */
		glfwPollEvents();
	}

}
