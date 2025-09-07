#include "MovementSystem.h"

#include "Coordinator.h"
#include "components/Direction.h"
#include "components/PhysicsBody.h"
#include "components/Velocity.h"

namespace ms::systems {
	void MovementSystem::update(float dt) {
		for (const auto entity : entities) {
			auto& direction = coordinator.get().getComponent<components::Direction>(entity);
			auto& physicsBody = coordinator.get().getComponent<components::PhysicsBody>(entity);
			auto& velocity = coordinator.get().getComponent<components::Velocity>(entity);

			b2Vec2 b2Direction{ direction.x, direction.y };
			physicsBody.shape->applyForce(b2Direction, velocity.velocity * dt);
		}
	}
}
