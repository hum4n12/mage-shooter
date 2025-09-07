#include "InputSystem.h"
#include "Coordinator.h"

#include "components/Direction.h"
#include "components/Input.h"

namespace {
    void handleKey(ms::components::Direction& direction, sf::Keyboard::Key key) {
        switch (key) {
        case sf::Keyboard::W:
            direction.y = -1.0f;
            break;
        case sf::Keyboard::S:
            direction.y = 1.0f;
            break;
        case sf::Keyboard::A:
            direction.x = -1.0f;
            break;
        case sf::Keyboard::D:
            direction.x = 1.0f;
            break;
        }
    }

    void clearKey(ms::components::Direction& direction, sf::Keyboard::Key key, const std::unordered_set<sf::Keyboard::Key>& keyPressed) {
        using KEY = sf::Keyboard;
        switch (key) {
        case KEY::W:
            if (keyPressed.count(KEY::S)) {
                direction.y = 1.0f;
            }
            else {
                direction.y = 0.f;
            }
            break;
        case sf::Keyboard::S:
            if (keyPressed.count(KEY::W)) {
                direction.y = -1.0f;
            }
            else {
                direction.y = 0.f;
            }
            break;
        case sf::Keyboard::A:
            if (keyPressed.count(KEY::D)) {
                direction.x = 1.0f;
            }
            else {
                direction.x = 0.f;
            }
            break;
        case sf::Keyboard::D:
            if (keyPressed.count(KEY::A)) {
                direction.x = -1.0f;
            }
            else {
                direction.x = 0.f;
            }
            break;
        }
    }
}

namespace ms::systems {
	void InputSystem::update(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            sf::Keyboard::Key key = event.key.code;
            if (event.type == sf::Event::KeyPressed) {
                keyPressed.insert(key);
                for (const auto& entity : entities) {
                    auto& direction = coordinator.get().getComponent<components::Direction>(entity);
                    handleKey(direction, key);
                }
            } 
                
            if (event.type == sf::Event::KeyReleased) {
                keyPressed.erase(key);
                for (const auto& entity : entities) {
                    auto& direction = coordinator.get().getComponent<components::Direction>(entity);
                    clearKey(direction, event.key.code, keyPressed);
                }
            }
        }
	}
}