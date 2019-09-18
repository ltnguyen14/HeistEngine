#include "hspch.h"
#include "ComponentManager.h"

namespace Heist {

	void ComponentManager::AddEntity(Entity& entity) {
		auto got = entities.find(entity.id);

		HS_CORE_ASSERT(got == entities.end(), "Trying to add the same entity twice! " + entity.name);
		entities.insert({ entity.id, {} });
	}

}