#include "hspch.h"
#include "BaseSystem.h"

namespace Heist {

	ComponentManager* BaseSystem::componentManager = nullptr;

	void BaseSystem::SubscribeToManager(ComponentManager *componentManager) {
		componentManager = componentManager;
	}

}