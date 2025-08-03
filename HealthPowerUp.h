#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Effects.h"

class HealthPowerUp {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool active = false;

public:
    HealthPowerUp() {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/HitPoints.png")) {
            std::cerr << "Failed to load heart texture!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.12f, 0.12f);
        resetPosition();
    }

    void resetPosition() {
        sprite.setPosition(rand() % 700, -80); // Random X, above top
    }

    void update(int health) {
        if (active) {
            sprite.move(0, 3.0f);
            if (sprite.getPosition().y > 800) deactivate(); 
        }
    }

    bool checkCollision(const sf::FloatRect& bounds) {
        return sprite.getGlobalBounds().intersects(bounds);
    }

    bool applyEffect(Player& player) {
            player.triggerGlow();
            resetPosition();
            return true;
    }

    void activate() { active = true; }
    void deactivate() { active = false; }
    bool isActive() const { return active; }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};
