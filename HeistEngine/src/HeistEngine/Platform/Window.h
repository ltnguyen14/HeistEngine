#pragma once
#include "Core/Event/EventNode.h"
#include "GLFW/glfw3.h"

namespace Heist {
	struct Window : public EventNode {
		Window(int32 width, int32 height, std::string title);
		~Window();

		void StartUp() override;
		void ShutDown() override;

		void SwapBuffer();
		void PollEvents();

		inline bool ShouldClose() { return glfwWindowShouldClose(window); };

	public:
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void window_size_callback(GLFWwindow* window, int width, int height);

	public:
		GLFWwindow* window;
		int32 width, height;
		std::string title;
	};
}
