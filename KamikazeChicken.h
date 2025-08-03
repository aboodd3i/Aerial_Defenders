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
        sprite.setScale(0.13f, 0.13f);
        sprite.setPosition(x, y);
        health = 1; 
        isCharging = false;
    }

    void update() override {
        sprite.move(-2.0f, 1.5);
        if (sprite.getPosition().x < 1000) { // starts charging when player is close
            isCharging = true;
            sprite.move(-15.0f, 0);
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
