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

  void mouse_callback(GLFWwindow *window, real64 xpos, real64 ypos) {
    Window *win = (Window*)glfwGetWindowUserPointer(window);

    MousePositionEvent *event = (MousePositionEvent*)win->g_memoryManager->Alloc(sizeof(MousePositionEvent));
    new(event) MousePositionEvent(xpos, ypos);

    win->SendEvent(event);
  }

	void window_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->width = width;
		win->height = height;
		win->resize = true;
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}

  void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    Window *win = (Window*)glfwGetWindowUserPointer(window);

    KeyEvent *event = (KeyEvent*)win->g_memoryManager->Alloc(sizeof(KeyEvent));
    new(event) KeyEvent(button, action);

    win->SendEvent(event);
  }

  void scroll_callback(GLFWwindow *window, real64 xoffset, real64 yoffset) {
    Window *win = (Window*)glfwGetWindowUserPointer(window);

    ScrollEvent *event = (ScrollEvent*)win->g_memoryManager->Alloc(sizeof(ScrollEvent));
    new(event) ScrollEvent(xoffset, yoffset);

    win->SendEvent(event);
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
		glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

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

  void Window::OnNotify(Event *event) {
    if (event->eventTypeMask == (INPUT | MOUSE | POSITION | SET)) {
			MousePositionSetEvent *mouseEvent = dynamic_cast<MousePositionSetEvent*>(event);
			HS_CORE_ASSERT(mouseEvent, "Error type casting event!");
      glfwSetCursorPos(window, mouseEvent->xpos, mouseEvent->ypos);
    }
  }
}
