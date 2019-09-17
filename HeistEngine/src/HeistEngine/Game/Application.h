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
#include "ECS/ComponentManager.h"
#include "ECS/BaseSystem.h"

namespace Heist {

	struct TestComponent : public BaseComponent {
		TestComponent(int32 x, int32 y) : x(x), y(y) {};
		int32 x;
		int32 y;

		static int32 componentTypeId;
		static std::string name;
	};

	struct TestComponent2 : public BaseComponent {
		TestComponent2(int32 x, int32 y) : x(x), y(y) {};
		int32 x;
		int32 y;

		static int32 componentTypeId;
		static std::string name;
	};

	struct TestSystem : public BaseSystem {
		TestSystem() {};

		static void Update(real32 delta);
	};

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
		std::shared_ptr<Camera> camera;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexArray> vertexArray2;
		std::shared_ptr<VertexArray> vertexArray3;
		std::shared_ptr<Texture> textureAtlas;
		std::shared_ptr<ComponentManager> componentManager;
	};
	
	// To be defined in client
	Application* CreateApplication();
}