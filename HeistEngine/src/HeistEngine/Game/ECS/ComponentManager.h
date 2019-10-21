#pragma once
#include "BaseComponent.h"
#include "Entity.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"

namespace Heist {

	struct ComponentManager {
	public:
		
		template<class T>
		void AddComponentType();

		void AddEntity(Entity& entity);

		template<class T>
		void AddComponents(Entity& entity, const std::initializer_list<T>& initializer);

		template<class T>
		std::unordered_map<int32, std::shared_ptr<BaseComponent>> GetComponents();

		std::unordered_map<int32, std::unordered_map<int32, std::shared_ptr<BaseComponent>>> components;
		std::unordered_map<int32, std::vector<std::shared_ptr<BaseComponent>>> entities;
	};

	template<class T>
	inline void ComponentManager::AddComponentType() {
		auto got = components.find(T::componentTypeId);

		if (got == components.end()) {
			T::componentTypeId = ++s_componentId;
			components.insert({ T::componentTypeId, {} });
		} else {
			HS_CORE_WARN("Trying to register component type {} twice!", T::name);
		}

	}

	template<class T>
	inline void ComponentManager::AddComponents(Entity& entity, const std::initializer_list<T>& initializer) {
		auto got = components.find(T::componentTypeId);
		HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component Type Id!");

		auto ent = entities.find(entity.id);
		HS_CORE_ASSERT(ent != entities.end(), "Trying to add to unknown entity!");

		for (auto i : initializer) {
			std::shared_ptr<T> newComponent = std::make_shared<T>(T(i));
			entities[entity.id].push_back(newComponent);
			components[T::componentTypeId][entity.id] = newComponent;
		}
	}

	template<class T>
	inline std::unordered_map<int32, std::shared_ptr<BaseComponent>> ComponentManager::GetComponents() {
		 auto got = components.find(T::componentTypeId);
		 HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component Type Id!");

		 auto rawRes = components[T::componentTypeId];

		 return rawRes;
	}

}
