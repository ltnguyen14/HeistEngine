#pragma once
#include "Core/Event/EventNode.h"

namespace Heist {

	struct Layer {

		Layer(std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		std::string layerName;

	};
}