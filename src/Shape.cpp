#include "Shape.h"
#include <array>


namespace ms {
    PolygonShape::PolygonShape(b2WorldId world, unsigned int verticesCount, ms::Unit<float, ms::UnitTag::Pixels> radius, const b2ShapeDef& fixture) : Shape(world) {
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

        shape.setPointCount(verticesCount);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(0.f, 0.f);

        for (int i = 0; i < polygon.count; i++) {
            b2Vec2 vertice = polygon.vertices[i];
            shape.setPoint(i, sf::Vector2f{ vertice.x * SCALE, -vertice.y * SCALE});
        }

        for (int i = 0; i < verticesCount; i++) {
            const auto& pos = shape.getPoint(i);
        }
    }

    void PolygonShape::draw(sf::RenderTarget& render) {
        align();
        render.draw(shape);
    }

    RectangleShape::RectangleShape(b2WorldId world, ms::Unit<float, ms::UnitTag::Pixels> width, ms::Unit<float, ms::UnitTag::Pixels> height, const b2ShapeDef& fixture) : Shape(world) {
        b2Polygon polygon = b2MakeBox(width / 2 / SCALE, height / 2 / SCALE);
        shapeId = b2CreatePolygonShape(bodyId, &fixture, &polygon);
        
        shape.setSize({ width, height });
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(polygon.centroid.x * SCALE, -polygon.centroid.y * SCALE);
    }

    void RectangleShape::draw(sf::RenderTarget& render) {
        align();
        const auto& [x, y] = shape.getPosition();
        const auto& [width, height] = shape.getSize();
        shape.setPosition(x - width / 2, y - height / 2);
        render.draw(shape);
    }
}