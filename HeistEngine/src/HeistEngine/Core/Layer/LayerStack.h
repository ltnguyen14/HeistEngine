#pragma once
#include "Layer.h"

namespace Heist {
	struct LayerStack {

		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer, const std::shared_ptr<ComponentManager>& componentManager);
		void PopLayer(Layer* layer);

		std::vector<Layer*> layers;

	};
}