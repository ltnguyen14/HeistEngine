#pragma once
#include "Core/Event/EventNode.h"
#include "Core/Renderer/Camera.h"
#include "Game/ECS/ComponentManager.h"
#include "Core/Renderer/Model.h"

namespace Heist {

	struct Layer {

		Layer(std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(const std::shared_ptr<ComponentManager>& componentManager) {}
		virtual void OnDetach() {}
		virtual void OnOverlay() {}
		virtual void OnUpdate(real64 time) {}
		virtual void OnRender(const std::shared_ptr<Camera>& camera) {}
		virtual void OnWindowResize(real32 left, real32 right, real32 bottom, real32 top) {}

		std::string layerName;
		std::shared_ptr<ComponentManager> componentManager;
		Light3D light;
	};
}
