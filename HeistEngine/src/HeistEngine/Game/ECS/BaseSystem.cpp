#include "hspch.h"
#include "BaseSystem.h"

namespace Heist {

	std::shared_ptr<ComponentManager> BaseSystem::componentManager = nullptr;

	void BaseSystem::RegisterComponentManager(std::shared_ptr<ComponentManager> componentManager) {
		BaseSystem::componentManager = componentManager;
	}

}