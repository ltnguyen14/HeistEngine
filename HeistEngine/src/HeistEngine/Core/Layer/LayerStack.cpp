#include "hspch.h"
#include "LayerStack.h"

namespace Heist {

	LayerStack::LayerStack() {
	
	}

	LayerStack::~LayerStack() {
	
	}

	void LayerStack::PushLayer(Layer* layer, const std::shared_ptr<ComponentManager>& componentManager) {
		layers.push_back(layer);
		layer->OnAttach(componentManager);
	}

	void LayerStack::PopLayer(Layer *layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);

		if (it != layers.end()) {
			layer->OnDetach();
			layers.erase(it);
		}
	}
}