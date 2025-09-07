#include "GameManager.h"
#include "GlobalConfig.h"
#include "components/PhysicsBody.h"
#include "components/Direction.h"
#include "components/Input.h"
#include "components/Velocity.h"

#include <box2d/box2d.h>

namespace ms {
	void GameManager::init() {
        coordinator.init();
        inputSystem = systemFactory.getInputSystem();
        movementSystem = systemFactory.getMovementSystem();
        drawSystem = systemFactory.getDrawSystem();

		window.create(sf::VideoMode(GlobalConfig::WINDOW_WIDTH, GlobalConfig::WINDOW_HEIGHT), std::string(GlobalConfig::GAME_NAME));
		window.setFramerateLimit(60);

        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = { 0.f, 0.f };
        world = b2CreateWorld(&worldDef);
	}

	void GameManager::run() {
        Entity player = coordinator.createEntity();
        coordinator.addComponent<components::Direction>(player);
        coordinator.addComponent<components::Input>(player);
        components::PhysicsBody pr{};
        //pr.shape = std::make_unique<RectangleShape>(world, ms::Unit<float, ms::UnitTag::Pixels>{50.0f}, ms::Unit<float, ms::UnitTag::Pixels>{ 50.0f });
        pr.shape = std::make_unique<PolygonShape>(world, 8u, ms::Unit<float, ms::UnitTag::Pixels>{10.0f});
        pr.shape->setTransform({ 150.0f, 50.0f });
        pr.shape->setBodyType(b2_dynamicBody);
        coordinator.addComponent<components::PhysicsBody>(player, std::move(pr));
        coordinator.addComponent<components::Velocity>(player, { 500.0f });

        Entity entity = coordinator.createEntity();
        components::PhysicsBody pb{};
        pb.shape = std::make_unique<PolygonShape>(world, 5u, ms::Unit<float, ms::UnitTag::Pixels>{30.0f});
        pb.shape->setBodyType(b2_staticBody);
        pb.shape->setTransform({ 50.0f, 50.0f });
        coordinator.addComponent<components::PhysicsBody>(entity, std::move(pb));

        while (window.isOpen()) {
            sf::Time dt = clock.restart();
            
            inputSystem->update(window);
            
            update(dt.asSeconds());
            window.clear();
            draw();
            window.display();
        }
	}

    void GameManager::update(float dt) {
        b2World_Step(world, dt, 4);
        movementSystem->update(dt);
    }

    void GameManager::draw() {
        drawSystem->draw(window);
    }
}
