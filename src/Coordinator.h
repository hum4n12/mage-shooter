#pragma once
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "SystemManager.h"

#include <unordered_map>
#include <vector>
#include <any>
#include <typeindex>
#include <type_traits>

namespace ms {

	using Entity = uint64_t;

	class Coordinator {
	public:
		void init();
		void update(float dt);

		Entity createEntity();
		void destroyEntity(Entity entity);

		template<typename TComponent>
		void addComponent(Entity entity, TComponent&& component = {});

		template <typename TComponent>
		TComponent& getComponent(Entity entity);

		template <typename TComponent>
		ComponentType getComponentType();

		template <typename TComponent>
		void removeComponent(Entity entity);
		
		template <typename TSystem>
		std::shared_ptr<TSystem> registerSystem();

		template <typename TSystem>
		void setSystemSignature(Signature signature);

		template <typename TSystem>
		std::expected<std::shared_ptr<TSystem>, std::monostate> getSystem();

	private:
		void registerComponents();

		EntityManager entityManager;
		ComponentsManager componentsManager;
		SystemManager systemManager;
	};

	template<typename TComponent>
	inline void Coordinator::addComponent(Entity entity, TComponent&& component) {
		componentsManager.addComponent<TComponent>(entity, std::move(component));
		auto signature = entityManager.getSignature(entity);
		signature.set(componentsManager.getComponentType<TComponent>(), true);
		entityManager.setSignature(entity, signature);
		systemManager.entitySignatureChanged(entity, signature);
	}

	template<typename TComponent>
	inline void Coordinator::removeComponent(Entity entity) {
		componentsManager.removeComponent<TComponent>(entity);
		auto signature = entityManager.getSignature(entity);
		signature.set(componentsManager.getComponentType<TComponent>(), false);
		entityManager.setSignature(entity, signature);
		systemManager.entitySignatureChanged(entity, signature);
	}
	
	template <typename TComponent>
	inline TComponent& Coordinator::getComponent(Entity entity) {
		return componentsManager.getComponent<TComponent>(entity);
	}

	template <typename TComponent>
	inline ComponentType Coordinator::getComponentType() {
		return componentsManager.getComponentType<TComponent>();
	}

	template <typename TSystem>
	inline std::shared_ptr<TSystem> Coordinator::registerSystem() {
		static_assert(std::is_base_of<systems::System, TSystem>::value && "TSystem type does not inherit from System");
		return systemManager.registerSystem<TSystem>(*this);
	}

	template<typename TSystem>
	inline void Coordinator::setSystemSignature(Signature signature) {
		systemManager.setSignature<TSystem>(signature);
	}

	template <typename TSystem>
	std::expected<std::shared_ptr<TSystem>, std::monostate> Coordinator::getSystem() {
		return systemManager.getSystem<TSystem>();
	}
}
