#pragma once
#include "GlobalConfig.h"
#include "Coordinator.h"

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "systems/SystemFactory.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/DrawSystem.h"

namespace ms {

	class GameManager {
	public:
		GameManager() = default;
		void init();
		void run();
	private:
		void update(float dt);
		void draw();

		sf::RenderWindow window;
		sf::Clock clock;
		Coordinator coordinator;
		b2WorldId world;
		systems::SystemFactory systemFactory{ coordinator };
		std::shared_ptr<systems::InputSystem> inputSystem;
		std::shared_ptr<systems::MovementSystem> movementSystem;
		std::shared_ptr<systems::DrawSystem> drawSystem;
	};

}