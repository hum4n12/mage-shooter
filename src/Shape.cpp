#include "Shape.h"
#include <array>


namespace ms {
    PolygonShape::PolygonShape(b2WorldId world, unsigned int verticesCount, ms::Unit<float, ms::UnitTag::Pixels> radius, const b2ShapeDef& fixture) : Shape(world) {
		shape = std::make_unique<sf::ConvexShape>();
		sf::ConvexShape* sfPolygon = dynamic_cast<sf::ConvexShape*>(shape.get());

		const float offset = verticesCount % 2 == 0 ? B2_PI / verticesCount : B2_PI / 2.0f;
		std::array<b2Vec2, B2_MAX_POLYGON_VERTICES> vertices;

		for (int i = 0; i < verticesCount && i < B2_MAX_POLYGON_VERTICES; ++i) {
			float angle = i * 2 * B2_PI / verticesCount + offset;
			auto& verticePos = vertices[i];
			verticePos.x = radius / SCALE * std::cos(angle);
			verticePos.y = -radius / SCALE * std::sin(angle);
		}

		b2Hull hull = b2ComputeHull(vertices.data(), verticesCount);
		b2Polygon polygon = b2MakePolygon(&hull, 0.01f);
		shapeId = b2CreatePolygonShape(bodyId, &fixture, &polygon);

		sfPolygon->setPointCount(verticesCount);
		sfPolygon->setFillColor(sf::Color::Green);
		sfPolygon->setOrigin(0.f, 0.f);

		for (int i = 0; i < polygon.count; i++) {
			b2Vec2 vertice = polygon.vertices[i];
			sfPolygon->setPoint(i, sf::Vector2f{ vertice.x * SCALE, -vertice.y * SCALE });
		}

		for (int i = 0; i < verticesCount; i++) {
			const auto& pos = sfPolygon->getPoint(i);
		}
    }

    void PolygonShape::draw(sf::RenderTarget& render) {
        align();
        render.draw(*shape);
    }

    RectangleShape::RectangleShape(b2WorldId world, ms::Unit<float, ms::UnitTag::Pixels> width, ms::Unit<float, ms::UnitTag::Pixels> height, const b2ShapeDef& fixture) : Shape(world) {
        b2Polygon polygon = b2MakeBox(width / 2 / SCALE, height / 2 / SCALE);
		shape = std::make_unique<sf::RectangleShape>();
		sf::RectangleShape& sfRectangle = dynamic_cast<sf::RectangleShape&>(*shape);
        shapeId = b2CreatePolygonShape(bodyId, &fixture, &polygon);
        
		sfRectangle.setSize({ width, height });
		sfRectangle.setFillColor(sf::Color::Blue);
		sfRectangle.setOrigin(polygon.centroid.x * SCALE, -polygon.centroid.y * SCALE);
    }

    void RectangleShape::draw(sf::RenderTarget& render) {
        align();
		sf::RectangleShape& sfRectangle = dynamic_cast<sf::RectangleShape&>(*shape);
        const auto& [x, y] = sfRectangle.getPosition();
        const auto& [width, height] = sfRectangle.getSize();
		sfRectangle.setPosition(x - width / 2, y - height / 2);
        render.draw(sfRectangle);
    }
}