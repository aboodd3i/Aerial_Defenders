#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Bullet.h"
#include "Effects.h"

class Enemy {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    Bullet* bullets[10];
    sf::Clock shootClock;
    int health = 1;
    int bulletCount = 0;

public:
    Enemy(float x, float y) {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Regular_Chicken.png")) {
            std::cout << "Failed to load enemy image!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.15f, 0.15f);
        sprite.setPosition(x, y);

        for (int i = 0; i < 10; ++i)
            bullets[i] = nullptr;
    }

    // Virtual functions for polymorphic behavior
    virtual void update() {
        sprite.move(-2.0f, 1.0);

        // Automatic shooting
        if (shootClock.getElapsedTime().asSeconds() > 1.5f && bulletCount < 10) {
            shoot();
            shootClock.restart();
        }
    }

    virtual void shoot() {
        sf::Vector2f pos = sprite.getPosition();
        bullets[bulletCount++] = new Bullet(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 2, "C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Bullet_Enemy.png", 5.0f);
    }

    virtual void updateBullets() {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i]) {
                bullets[i]->moveDown();
                if (bullets[i]->getPosition().y > 800) {
                    delete bullets[i];
                    for (int j = i; j < bulletCount - 1; ++j)
                        bullets[j] = bullets[j + 1];
                    bullets[--bulletCount] = nullptr;
                    --i;
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void drawBullets(sf::RenderWindow& window) {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i])
                bullets[i]->draw(window);
        }
    }

    virtual void onHit() {
        health--;
        Effects::triggerShake(3.0f, 0.2f);
        if (health <= 0) onDeath();
    }

    virtual void onDeath() {
        Effects::triggerShake(5.0f, 0.3f);
    }

    virtual bool isAlive() const {
        return health > 0;
    }

    virtual sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();  // Returns the enemy's bounding box
    }


    virtual bool isOffScreen() const {
        return sprite.getPosition().y > 800;
    }

    Bullet** getBullets() {
        return bullets;
    }

    virtual ~Enemy() {
        for (int i = 0; i < bulletCount; ++i)
            delete bullets[i];
    }
};
