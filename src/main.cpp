#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Shape.h"
#include "GlobalConfig.h"

int main() {
    using ut = ms::UnitTag;
    sf::RenderWindow window(sf::VideoMode(GlobalConfig::WINDOW_WIDTH, GlobalConfig::WINDOW_HEIGHT), "Box2D + SFML");
    window.setFramerateLimit(60);
    
    b2Vec2 gravity(0.0f, -10.0f);
    b2WorldDef worldDef = b2DefaultWorldDef();
    b2WorldId world = b2CreateWorld(&worldDef);

    ms::PolygonShape p1{ world, 5u, ms::Unit<float, ms::UnitTag::Pixels>{30.0f} };
    p1.setBodyType(b2_dynamicBody);
    p1.setTransform({ 50.0f, 50.0f }, b2MakeRot(- 0.01f));

    ms::RectangleShape r2{ world, ms::Unit<float, ut::Pixels>{400.0f}, ms::Unit<float, ut::Pixels>{50.0f} };
    r2.setTransform({ 50.0f, 500.0f });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float timeStep = 1.0f / 60.0f;
        b2World_Step(world, timeStep, 4);    
        window.clear();
        p1.draw(window);
        r2.draw(window);
        window.display();
    }

	return 0;
}