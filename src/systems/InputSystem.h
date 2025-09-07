#pragma once
#include "systems/System.h"
#include "components/Input.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <unordered_set>

namespace ms::systems {
	class InputSystem : public System {
	public:
		using System::System;
		void update(sf::RenderWindow& window);
	private:
		std::unordered_set<sf::Keyboard::Key> keyPressed;
	};
}