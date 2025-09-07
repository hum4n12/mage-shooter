#include "DrawSystem.h"
#include "Coordinator.h"

#include "components/PhysicsBody.h"

namespace ms::systems {
	void DrawSystem::draw(sf::RenderTarget& render) {
		for (const auto entity : entities) {
			auto& physicsBody = coordinator.get().getComponent<components::PhysicsBody>(entity);
			physicsBody.shape->draw(render);
		}
	}
}