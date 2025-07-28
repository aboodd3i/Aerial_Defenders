#pragma once
#include "Enemy.h"

class KamikazeChicken : public Enemy {
private:
    float chargeSpeed;;
    bool isCharging;

public:
    KamikazeChicken(float x, float y) : Enemy(x, y) {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Kamikaze_Chicken.png")) {
            std::cout << "Failed to load enemy image!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.15f, 0.15f);
        sprite.setPosition(x, y);
        health = 1; 
        isCharging = false;
        chargeSpeed = 5.0f;
    }

    void update() override {
        // Start charging when player is close
        if (sprite.getPosition().x < 200 && !isCharging) {
            sprite.move(-2.0f, 1.0);
            isCharging = true;
            Enemy::update();
        }

        
    }

     void onDeath() override {
        Effects::triggerShake(8.0f, 0.4f); // Bigger shake on death
     }

    void draw(sf::RenderWindow& window) {
        if (isCharging) {
            sprite.setColor(sf::Color::Red); // Visual charging indicator
        }
        Enemy::draw(window);
    }
};
