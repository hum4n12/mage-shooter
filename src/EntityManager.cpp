#include "EntityManager.h"
#include <cassert>

namespace ms {
	Entity EntityManager::createEntity() {
		if (availableEntities.empty()) {
			signatures.push_back(Signature{});
			return signatures.size() - 1;
		}

		Entity id = availableEntities.front();
		availableEntities.pop();
		signatures[id].reset();
		return id;
	}

	void EntityManager::destroyEntity(Entity entity) {
		assert(entity < signatures.size() && "Entity out of range");
		
		availableEntities.push(entity);
		signatures[entity].reset();
	}

	Signature EntityManager::getSignature(Entity entity) const {
		assert(entity < signatures.size() && "Entity out of range");
		
		return signatures[entity];
	}

	void EntityManager::setSignature(Entity entity, Signature signature) {
		assert(entity < signatures.size() && "Entity out of range");

		signatures[entity] = signature;
	}
}
