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
#include "Core/FileSystem/FileManager.h"
#include "Core/Math/Math.h"
#include "Platform/Assertions.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"

namespace Heist {

	class Application {
	public:
		Application(int32 width, int32 height, std::string title);
		virtual ~Application();

		void OnUpdate(real64 time);
		void OnRender();

		void PushLayer(Layer *layer);
		void PopLayer(Layer *layer);

		void Run();

	private:
		bool running;
		EventBus eventBus;
		LayerStack layerStack;
		Window window;
		MemoryManager *memoryManager;
		InputManager *inputManager;
	};
	
	// To be defined in client
	Application* CreateApplication();
}