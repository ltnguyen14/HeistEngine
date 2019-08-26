#include "hspch.h"
#include "LayerStack.h"

namespace Heist {

	LayerStack::LayerStack() {
	
	}

	LayerStack::~LayerStack() {
	
	}

	void LayerStack::PushLayer(Layer* layer) {
		layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer *layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);

		if (it != layers.end()) {
			layer->OnDetach();
			layers.erase(it);
		}
	}
}