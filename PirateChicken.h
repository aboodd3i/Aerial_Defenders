#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include <iostream>

class PirateChicken : public Enemy{
private:
    int hitPoints;

public:
    PirateChicken(float x, float y) : Enemy(x, y), hitPoints(2) {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Pirate_Chicken.png")) {
            std::cout << "Failed to load enemy image!" << std::endl;
        }

    }

    // Virtual functions for polymorphic behavior
    virtual void update() {
        sprite.move(-2.5f, 1.5);

        // Automatic shooting
        if (shootClock.getElapsedTime().asSeconds() > 2.f && bulletCount < 10) {
            shoot();
            shootClock.restart();
        }
    }

    virtual void shoot() {
        sf::Vector2f pos = sprite.getPosition();
        bullets[bulletCount++] = new Bullet(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 2, "C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Bullet_PirateEnemy.png", 8.0f);
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

    //checking for collision with a bullet
    bool takeHit() {
        hitPoints--;
        return hitPoints <= 0; // true when 2 bullets are hit
    }
};
