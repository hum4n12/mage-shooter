#include "Coordinator.h"
#include "components/Transform.h"
#include "components/PhysicsBody.h"
#include "components/Direction.h"
#include "components/Input.h"
#include "components/Velocity.h"

#include "systems/MovementSystem.h"

namespace ms {
	void Coordinator::init() {
		registerComponents();
	}

	Entity Coordinator::createEntity() {
		return entityManager.createEntity();
	}

	void Coordinator::destroyEntity(Entity entity) {
		entityManager.destroyEntity(entity);
		componentsManager.entityDestroyed(entity);
		systemManager.entityDestroyed(entity);
	}

	void Coordinator::registerComponents() {
		componentsManager.registerComponent<components::Transform>();
		componentsManager.registerComponent<components::PhysicsBody>();
		componentsManager.registerComponent<components::Direction>();
		componentsManager.registerComponent<components::Input>();
		componentsManager.registerComponent<components::Velocity>();
	}
}