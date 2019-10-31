#include "hspch.h"
#include "ComponentManager.h"

namespace Heist {

	void ComponentManager::AddEntity(Entity& entity) {
		HS_CORE_ASSERT(entities.find(entity.id) == entities.end(), "Trying to add the same entity twice! " + entity.name);
		entities.insert({ entity.id, {} });
	}

}