#pragma once
#include "../Macro.h"
#include "Platform/Window.h"
#include "Core/Event/EventBus.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Memory/Memory.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/Camera.h"
#include "Core/Renderer/Texture.h"
#include "Core/Manager/InputManager.h"

namespace Heist {
	class Application {
	public:
		Application(int32 width, int32 height, std::string title);
		virtual ~Application();

		void OnUpdate(real64 time);
		void OnRender();

		void PushLayer(Layer *layer);
		void PopLayer(Layer* layer);

		void Run();

	private:
		bool running;
		EventBus eventBus;
		LayerStack layerStack;
		Window window;
		MemoryManager memoryManager;
		InputManager inputManager;
		std::shared_ptr<Camera> camera;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexArray> vertexArray2;
		std::shared_ptr<VertexArray> vertexArray3;
		std::shared_ptr<Texture> textureAtlas;
	};
	
	// To be defined in client
	Application* CreateApplication();
}