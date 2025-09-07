#pragma once
#include <bitset>
#include <typeindex>
#include <typeinfo>

namespace ms {
	constexpr uint32_t MAX_COMPONENTS_COUNT = 32u;
	using Entity = uint64_t;
	using Index = uint64_t;
	using ComponentType = uint8_t;
	using Signature = std::bitset<MAX_COMPONENTS_COUNT>;

	template <typename T>
	std::type_index calculateKey() {
		return std::type_index(typeid(T));
	}
}