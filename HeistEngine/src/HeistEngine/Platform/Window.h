#pragma once
#include "Core/Event/EventNode.h"
#include "GLFW/glfw3.h"

namespace Heist {
	struct Window : public EventNode {
		Window(EventBus *eventBus, int32 width, int32 height, std::string title);
		~Window();

		void SwapBuffer();
		void PollEvents();
		void OnNotify(Event event) override;
		void ClearWindow();

		inline bool ShouldClose() { return glfwWindowShouldClose(window); };

		GLFWwindow* window;
		int32 width, height;
		std::string title;
	};
}
