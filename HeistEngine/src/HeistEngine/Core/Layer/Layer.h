#pragma once
#include "Core/Event/EventNode.h"

namespace Heist {

	struct Layer {

		Layer(std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(real64 time) {}
		virtual void OnRender() {}
		virtual void OnWindowResize(real32 left, real32 right, real32 bottom, real32 top) {}

		std::string layerName;

	};
}