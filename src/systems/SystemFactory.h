#pragma once

#include "Coordinator.h"

#include "MovementSystem.h"
#include "DrawSystem.h"
#include "InputSystem.h"

namespace ms::systems {
	class SystemFactory {
	public:
		SystemFactory(Coordinator& coordinator);
		std::shared_ptr<MovementSystem> getMovementSystem();
		std::shared_ptr<DrawSystem> getDrawSystem();
		std::shared_ptr<InputSystem> getInputSystem();

	private:
		template <typename TSystem, typename ...TComponents>
		std::shared_ptr<TSystem> getSystem();
		std::reference_wrapper<Coordinator> coordinator;
	};

	template <typename TSystem, typename ...TComponents>
	inline std::shared_ptr<TSystem> SystemFactory::getSystem() {
		auto systemExpected = coordinator.get().getSystem<TSystem>();
		if (systemExpected) {
			return systemExpected.value();
		}

		auto system = coordinator.get().registerSystem<TSystem>();
		Signature signature;
		(signature.set(coordinator.get().getComponentType<TComponents>()), ...);
		coordinator.get().setSystemSignature<TSystem>(signature);
		return system;
	}
}