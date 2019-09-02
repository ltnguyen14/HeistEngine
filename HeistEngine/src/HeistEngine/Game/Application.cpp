#include "hspch.h"
#include "Application.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"

#include <glad/glad.h>

namespace Heist {

	Application::Application(int32 width, int32 height, std::string title) 
		: window(&eventBus, width, height, title), memoryManager(2 * 1024) {
		running = true;

		shader.reset(Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));

		// ----------------- Rendering
		real32 verticies[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		uint32 indicies[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		uint32 vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		indexBuffer.reset(IndexBuffer::Create(indicies, 6));
	}

	Application::~Application() {}

	void Application::OnUpdate(real64 time) {
	}

	void Application::OnRender() {
		window.ClearWindow();
		// Render stuff go here
		shader->Bind();
		vertexBuffer->Bind();
		indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->count, GL_UNSIGNED_INT, 0);
		// --------------------
		window.SwapBuffer();
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer) {
		layerStack.PopLayer(layer);
	}

	void Application::Run() {
		// Main loop setup
		real64 lag = 0.0f;
		real64 targetFPS = 60.0f;
		real64 MS_PER_UPDATE = 1000.0f / targetFPS;
		clock_t previous = clock();
		real32 frameTime = 0.0f;
		const int32 MAX_FRAME_SKIP = 10;
		int32 loops = 0;

		while (!window.ShouldClose()) {
			// Time stuff
			clock_t current = clock();
			auto elapsed = current - previous;

			previous = current;
			lag += elapsed;
			// ------

			// Update
			window.PollEvents();

			loops = 0;
			while (lag >= MS_PER_UPDATE && loops < MAX_FRAME_SKIP) {
				this->OnUpdate(MS_PER_UPDATE);
				lag -= MS_PER_UPDATE;
				loops++;
			}

			// Render
			this->OnRender();
			eventBus.Notify(); // TODO(LAM): Need to move this somewhere
			frameTime = float(clock() - current);
		};
	}
}