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

		std::unordered_map<int32, std::vector<std::shared_ptr<BaseComponent>>> components;
	};

	template<class T>
	inline void ComponentManager::AddComponentType() {
		T::componentTypeId = ++s_componentId;
		components.insert({ T::componentTypeId, {} });
	}

	template<class T>
	inline void ComponentManager::AddComponents(const std::initializer_list<T>& initializer) {
		auto got = components.find(T::componentTypeId);
		HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component Type Id!");

		for (auto i : initializer) {
			components[T::componentTypeId].push_back(std::shared_ptr<T>(new T(i)));
		}
	}

	template<class T>
	inline std::vector<T*> ComponentManager::GetComponents() {
		 auto got = components.find(T::componentTypeId);
		 HS_CORE_ASSERT(got != components.end(), "Trying to get unknown Component Type Id!");

		 auto rawRes = components[T::componentTypeId];

		 return std::vector<T*>();
	}
}