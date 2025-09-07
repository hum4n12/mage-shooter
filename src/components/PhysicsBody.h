#pragma once
#include "Shape.h"

#include <memory>

namespace ms::components {

	struct PhysicsBody {
		std::unique_ptr<Shape> shape;
	};

}
