#include "hspch.h"
#include "Layer.h"

namespace Heist {
	
	Layer::Layer(EventBus* eventBus, std::string name) : layerName(name), EventNode(eventBus, name) {
	
	}

	Layer::~Layer() {
	
	}
}