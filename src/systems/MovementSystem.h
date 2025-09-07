#pragma once
#include "System.h"

namespace ms::systems {
	class MovementSystem : public System {
	public:
		void update(float dt);
	};
}