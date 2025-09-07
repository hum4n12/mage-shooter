#pragma once
#include <box2d/types.h>

namespace ms::components {
	struct Transform {
		b2Vec2 position{ 0,0 };
		float rotation = 0;
	};
}