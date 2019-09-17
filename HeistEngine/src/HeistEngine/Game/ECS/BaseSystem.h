#pragma once
#include "ComponentManager.h"

namespace Heist {

	struct BaseSystem {
		BaseSystem() {};

		static void SubscribeToManager(ComponentManager* componentManager);
		virtual ~BaseSystem() {};

		static ComponentManager *componentManager;
	};

}