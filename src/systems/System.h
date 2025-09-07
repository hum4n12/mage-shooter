#pragma once
#include "Types.h"
#include <set>

namespace ms {
	class Coordinator;
}

namespace ms::systems {
	class System {
	public:
		System(Coordinator& coordinator) : coordinator(coordinator) {}
		void insertEntity(Entity entity);
		void removeEntity(Entity entity);
	protected:
		std::set<Entity> entities;
		std::reference_wrapper<Coordinator> coordinator;
	};
}