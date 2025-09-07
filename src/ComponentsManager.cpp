#include "ComponentsManager.h"

namespace ms {
	void ComponentsManager::entityDestroyed(Entity entity) {
		for (auto [_, componentsArray] : componentPools) {
			componentsArray->remove(entity);
		}
	}

	void ComponentsManager::compact() {
		for (auto [_, componentsArray] : componentPools) {
			componentsArray->compact();
		}
	}
}
