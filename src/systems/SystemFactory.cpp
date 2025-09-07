#include "SystemFactory.h"

#include "components/Transform.h"
#include "components/PhysicsBody.h"
#include "components/Direction.h"
#include "components/Player.h"
#include "components/Input.h"
#include "components/Velocity.h"

namespace ms::systems {
	using namespace components;

	SystemFactory::SystemFactory(Coordinator& coordinator) : coordinator(coordinator) {}

	std::shared_ptr<MovementSystem> SystemFactory::getMovementSystem() {
		return getSystem<MovementSystem, Direction, PhysicsBody, Velocity>();
	}

	std::shared_ptr<DrawSystem> SystemFactory::getDrawSystem() {
		return getSystem<DrawSystem, PhysicsBody>();
	}

	std::shared_ptr<InputSystem> SystemFactory::getInputSystem(){
		return getSystem<InputSystem, Direction, Input>();
	}
}
