#pragma once
#include "Layer.h"

namespace Heist {
	struct LayerStack {

		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer *layer);
		void PopLayer(Layer *layer);

		std::vector<Layer*> layers;

	};
}