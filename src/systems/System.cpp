#include "System.h"

namespace ms::systems {
	void System::insertEntity(Entity entity) {
		entities.insert(entity);
	}

	void System::removeEntity(Entity entity) {
		entities.erase(entity);
	}
}
