#pragma once

namespace ms {
    enum class UnitTag {
        Pixels,
        Meters
    };

    template<typename T, UnitTag Tag>
    struct Unit {
        T value;

        explicit Unit(T val) : value(val) {}

        operator T() const { return value; }

        friend std::ostream& operator<<(std::ostream& os, const Unit& u) {
            os << u.value;
            if constexpr (Tag == UnitTag::Pixels) os << " px";
            else if constexpr (Tag == UnitTag::Meters) os << " m";
            return os;
        }
    };
}