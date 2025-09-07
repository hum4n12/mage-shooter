#pragma once
#include "Types.h"

#include <vector>
#include <unordered_map>
#include <optional>
#include <cassert>

namespace ms{

	class IComponentsArray {
	public:
		virtual ~IComponentsArray() = default;
		virtual void remove(Entity entity) = 0;
		virtual void compact() = 0;
	};

	template <typename TComponent>
	class ComponentsArray : public IComponentsArray {
	public:

		void add(Entity entity, TComponent&& component);
		TComponent& get(Entity entity);
		void remove(Entity entity) override;
		void compact() override;

	private:
		std::vector<std::optional<TComponent>> components;
		std::unordered_map<Entity, Index> entityIndex;
		std::unordered_map<Index, Entity> indexEntity;
	};

	template<typename TComponent>
	inline void ComponentsArray<TComponent>::add(Entity entity, TComponent&& component) {
		components.emplace_back(std::move(component));
		auto index = components.size() - 1;
		entityIndex[entity] = index;
		indexEntity[index] = entity;
	}

	template<typename TComponent>
	inline TComponent& ComponentsArray<TComponent>::get(Entity entity) {
		const auto index = entityIndex.find(entity);
		assert(index != entityIndex.end() && "Component does not exist");
		return components[index->second].value();
	}

	template<typename TComponent>
	inline void ComponentsArray<TComponent>::remove(Entity entity) {
		auto indexIter = entityIndex.find(entity);
		if (indexIter == entityIndex.end()) {
			return;
		}

		auto index = indexIter->second;
		components[index] = std::nullopt;
		entityIndex.erase(entity);
		indexEntity.erase(index);
	}

	template<typename TComponent>
	inline void ComponentsArray<TComponent>::compact() {
		size_t write = 0;

		for (size_t i = 0; i < components.size(); ++i) {
			if (auto& component = components[i]; component) {
				if (write != i) {
					components[write] = std::move(component);
					components[i].reset();

					Entity entity = indexEntity[i];
					indexEntity.erase(i);
					indexEntity[write] = entity;
					entityIndex[entity] = write;
				}
				
				++write;
			}
			else {
				indexEntity.erase(i);
			}
		
		}

		components.resize(write);
	}
}