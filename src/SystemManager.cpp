#include "SystemManager.h"

namespace ms {
	void SystemManager::entityDestroyed(Entity entity) {
		for (auto& [_, system] : systems) {
			system->removeEntity(entity);
		}
	}

	void SystemManager::entitySignatureChanged(Entity entity, Signature signature) {
		for (auto& [systemId, system] : systems) {
			Signature systemSignature = signatures[systemId];

			if ((signature & systemSignature) == systemSignature) {
				system->insertEntity(entity);
			}
			else {
				system->removeEntity(entity);
			}
		}
	}
}
