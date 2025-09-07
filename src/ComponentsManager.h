#pragma once
#include "Types.h"
#include "ComponentsArray.h"

#include <unordered_map>
#include <vector>
#include <any>
#include <typeindex>
#include <memory>
#include <cassert>

namespace ms {
	using Entity = uint64_t;

	class ComponentsManager {
	public:

		template <typename TComponent>
		void registerComponent();

		template <typename TComponent>
		void addComponent(Entity entity, TComponent&& component = {});

		template <typename TComponent>
		TComponent& getComponent(Entity entity);

		template <typename TComponent>
		ComponentType getComponentType();

		template <typename TComponent>
		void removeComponent(Entity entity);

		void entityDestroyed(Entity entity);

		void compact();

	private:
		template <typename TComponent>
		ComponentsArray<TComponent>& getComponentsArray();

		ComponentType nextType = 0;
		std::unordered_map<std::type_index, ComponentType> componentTypes;
		std::unordered_map<std::type_index, std::shared_ptr<IComponentsArray>> componentPools;
	};

	template<typename TComponent>
	inline void ComponentsManager::registerComponent() {
		std::type_index id = calculateKey<TComponent>();
		assert((componentPools.find(id) == componentPools.end()) && "Component type already registered.");
		assert((componentPools.size() < static_cast<size_t>(MAX_COMPONENTS_COUNT)) && "Component types max limit reached.");

		componentTypes.emplace(id, nextType++);
		componentPools.emplace(id, std::make_shared<ComponentsArray<TComponent>>());
	}

	template<typename TComponent>
	inline void ComponentsManager::addComponent(Entity entity, TComponent&& component) {
		getComponentsArray<TComponent>().add(entity, std::move(component));
	}

	template<typename TComponent>
	inline TComponent& ComponentsManager::getComponent(Entity entity) {
		return getComponentsArray<TComponent>().get(entity);
	}

	template<typename TComponent>
	inline ComponentType ComponentsManager::getComponentType() {
		std::type_index id = calculateKey<TComponent>();
		return componentTypes[id];
	}

	template<typename TComponent>
	inline void ComponentsManager::removeComponent(Entity entity) {
		getComponentsArray<TComponent>().remove(entity);
	}

	template<typename TComponent>
	inline ComponentsArray<TComponent>& ComponentsManager::getComponentsArray() {
		std::type_index id = calculateKey<TComponent>();
		assert(componentPools.find(id) != componentPools.end() && "Component type not registered.");

		return *std::static_pointer_cast<ComponentsArray<TComponent>>(componentPools[id]);
	}
}