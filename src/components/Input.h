#pragma once

#include <vector>
#include <SFML/Window/Keyboard.hpp>

namespace ms::components {
	struct Input {
		std::vector<sf::Keyboard::Key> keysOrder;
	};
}