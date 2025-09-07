#pragma once
#include "GlobalConfig.h"
#include "Unit.h"

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <array>

namespace ms {
	constexpr float SCALE = 50.0f; // 1 meter = 50 pixels
	constexpr b2Rot ZERO_ROTATION = {1.0f, 0.0f};

	namespace {
		b2Vec2 normalizeVec(b2Vec2& v) {
			float length = std::sqrt(v.x * v.x + v.y * v.y);
			if (length <= 0.0f) {
				return v;
			}

			return { v.x / length, v.y / length };
		}
	}

	class Shape {
	public:
		virtual ~Shape() {
			b2DestroyBody(bodyId);
		}

		virtual void draw(sf::RenderTarget& render) = 0;
		
		void applyForce(b2Vec2 direction, float force) {
			direction.y = -direction.y; //adjustment for sfml axis
			direction = normalizeVec(direction);
			b2Body_SetLinearVelocity(bodyId, direction * force);
			//b2Body_ApplyForceToCenter(bodyId, direction * force, true);
		}

		void setBodyType(const b2BodyType type) {
			b2Body_SetType(bodyId, type);
		}

		void setTransform(const sf::Vector2f& pos, b2Rot rotation = ZERO_ROTATION) {
			b2Vec2 b2Pos{ pos.x / SCALE, (GlobalConfig::WINDOW_HEIGHT - pos.y) / SCALE };
			b2Body_SetTransform(bodyId, b2Pos, rotation);
		}

		b2BodyId getBody() const {
			return bodyId;
		}

	protected:
		Shape(b2WorldId world) : world(world) {
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyId = b2CreateBody(world, &bodyDef);
		}

		void align() {
			b2Vec2 bodyPosition = b2Body_GetPosition(bodyId);
			b2Rot rotation = b2Body_GetRotation(bodyId);
			float angle = atan2(rotation.s, rotation.c);

			shape->setRotation(-angle * 180.0f / B2_PI);
			shape->setPosition(bodyPosition.x * SCALE, GlobalConfig::WINDOW_HEIGHT - bodyPosition.y * SCALE);
		}

		b2WorldId world;
		b2BodyId bodyId;
		b2ShapeId shapeId;
		std::unique_ptr<sf::Shape> shape;
	};

	class PolygonShape : public Shape {
	public:
		PolygonShape(b2WorldId world, unsigned int verticesCount, ms::Unit<float, ms::UnitTag::Pixels> radius, const b2ShapeDef& fixture = b2DefaultShapeDef());
		void draw(sf::RenderTarget& render) override;
	};

	class RectangleShape : public Shape {
	public:
		RectangleShape(b2WorldId world, ms::Unit<float, ms::UnitTag::Pixels> width, ms::Unit<float, ms::UnitTag::Pixels> height, const b2ShapeDef& fixture = b2DefaultShapeDef());
		void draw(sf::RenderTarget& render) override;
	};
}