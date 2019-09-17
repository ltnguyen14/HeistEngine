#pragma once
#include "ComponentManager.h"

namespace Heist {

	struct BaseSystem {
		BaseSystem() {};

		virtual ~BaseSystem() {};
		virtual void Update(real32 delta) = 0;

		static void RegisterComponentManager(ComponentManager *componentManager);

		static ComponentManager *componentManager;
	};

}