#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

public:
    Bullet(float x, float y, const std::string& imagePath, float bulletSpeed = 18.0f) {
        if (!texture.loadFromFile(imagePath)) {
            std::cout << "Failed to load bullet image from: " << imagePath << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.13f, 0.13f);
        sprite.setPosition(x, y);
        speed = bulletSpeed;
    }


    void update() {
        sprite.move(speed, 0); // rightwards by default
    }

    void moveDown() {
        sprite.move(-speed,0); // leftwards for enemy
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
};
