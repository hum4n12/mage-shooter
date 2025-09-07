#pragma once
#include "Types.h"

#include <vector>
#include <queue>

namespace ms {
	class EntityManager {
	public:
		Entity createEntity();
		void destroyEntity(Entity entity);
		Signature getSignature(Entity entity) const;
		void setSignature(Entity entity, Signature signature);

	private:
		std::queue<Entity> availableEntities;
		std::vector<Signature> signatures;
	};
}