#include "hspch.h"
#include "BaseSystem.h"

namespace Heist {

	ComponentManager* BaseSystem::componentManager = nullptr;

	void BaseSystem::RegisterComponentManager(ComponentManager* componentManager) {
		BaseSystem::componentManager = componentManager;
	}

}