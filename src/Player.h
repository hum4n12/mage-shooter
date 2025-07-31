#pragma once
#include <box2d/box2d.h>
#include <memory>
#include "Shape.h"

namespace ms {
	class Player {
	public:
		Player(b2WorldId world);
	private:
		std::unique_ptr<PolygonShape> shape;
	};
}