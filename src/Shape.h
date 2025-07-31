#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "GlobalConfig.h"
#include "Unit.h"

namespace ms {
	constexpr float SCALE = 50.0f; // 1 meter = 50 pixels
	constexpr b2Rot ZERO_ROTATION = {1.0f, 0.0f};

	template<typename SFShape>
	class Shape {
	public:
		virtual ~Shape() {
			b2DestroyBody(bodyId);
		}

		virtual void draw(sf::RenderTarget& render) = 0;

		void align() {
			b2Vec2 bodyPosition = b2Body_GetPosition(bodyId);
			b2Rot rotation = b2Body_GetRotation(bodyId);
			float angle = atan2(rotation.s, rotation.c);

			shape.setRotation(-angle * 180.0f / B2_PI);
			shape.setPosition(bodyPosition.x * SCALE, GlobalConfig::WINDOW_HEIGHT - bodyPosition.y * SCALE);
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

		b2WorldId world;
		b2BodyId bodyId;
		b2ShapeId shapeId;
		SFShape shape;
	};

	class PolygonShape : public Shape<sf::ConvexShape> {
	public:
		PolygonShape(b2WorldId world, unsigned int verticesCount, ms::Unit<float, ms::UnitTag::Pixels> radius, const b2ShapeDef& fixture = b2DefaultShapeDef());
		void draw(sf::RenderTarget& render) override;
	};

	class RectangleShape : public Shape<sf::RectangleShape> {
	public:
		RectangleShape(b2WorldId world, ms::Unit<float, ms::UnitTag::Pixels> width, ms::Unit<float, ms::UnitTag::Pixels> height, const b2ShapeDef& fixture = b2DefaultShapeDef());
		void draw(sf::RenderTarget& render) override;
	};
}