#pragma once
#include "BaseComponent.h"
#include "Core/Log/Log.h"

namespace Heist {

	class ComponentManager {
	public:
		
		template<class T>
		void AddComponentType();

		template<class T>
		void AddComponents(const std::initializer_list<T>& initializer);

		template<class T>
		std::vector<T*> GetComponents();

		std::unordered_map<int32, std::vector<BaseComponent*>> componentCollections;
	};

	template<class T>
	inline void ComponentManager::AddComponentType() {
		T::componentTypeId = s_componentId++;
		components.insert({ T::componentTypeId, {} });
	}

	template<class T>
	inline void ComponentManager::AddComponents(const std::initializer_list<T>& initializer) {
		auto got = components.find(T::componentTypeId);
		HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component!");

		for (auto i : initializer) {
			components[T::componentTypeId].push_back((BaseComponent)i);
		}
	}

	template<class T>
	inline std::vector<T*> ComponentManager::GetComponents() {
		 auto got = components.find(T::componentTypeId);
		 HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component!");

		 auto rawRes = components[T::componentTypeId];

		 return std::vector<T*>();
	}
}