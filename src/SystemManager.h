#pragma once
#include "Types.h"
#include "systems/System.h"

#include <unordered_map>
#include <map>
#include <set>
#include <typeindex>
#include <type_traits>
#include <cassert>
#include <memory>
#include <optional>
#include <expected>
#include <variant>
#include <type_traits>

namespace ms {
	class SystemManager {
	public:
		template <typename TSystem>
		std::shared_ptr<TSystem> registerSystem(Coordinator& coordinator);

		template <typename TSystem>
		std::expected<std::shared_ptr<TSystem>, std::monostate> getSystem();

		template <typename TSystem>
		void setSignature(Signature signature);

		void entityDestroyed(Entity entity);

		void entitySignatureChanged(Entity entity, Signature signature);

	private:
		std::unordered_map<std::type_index, Signature> signatures;
		std::map<std::type_index, std::shared_ptr<systems::System>> systems;
	};

	template<typename TSystem>
	inline std::shared_ptr<TSystem> SystemManager::registerSystem(Coordinator& coordinator) {
		static_assert(std::is_base_of<systems::System, TSystem>::value && "TSystem type does not inherit from System");
		
		std::type_index id = calculateKey<TSystem>();
		assert(systems.find(id) == systems.end() && "System already registered");

		auto system = std::make_shared<TSystem>(coordinator);
		systems.emplace(id, system);
		signatures.emplace(id, Signature{});

		return system;
	}

	template<typename TSystem>
	inline void SystemManager::setSignature(Signature signature) {
		std::type_index id = calculateKey<TSystem>();
		assert(systems.find(id) != systems.end() && "System not registered");

		signatures[id] = signature;
	}

	template <typename TSystem>
	std::expected<std::shared_ptr<TSystem>, std::monostate> SystemManager::getSystem() {
		static_assert(std::is_base_of<systems::System, TSystem>::value && "TSystem type does not inherit from System");

		std::type_index id = calculateKey<TSystem>();
		auto system = systems.find(id);
		if (system == systems.end()) {
			return std::unexpected(std::monostate{});
		}

		return std::static_pointer_cast<TSystem>(system->second);
	}
}