#pragma once

#include "systems/System.h"
#include <SFML/Graphics.hpp>

namespace ms::systems {
	class DrawSystem : public System {
	public:
		void draw(sf::RenderTarget& render);
	};
}