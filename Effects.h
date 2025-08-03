#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 

class Effects {
private:
    static float shakeOffsetX; 
    static float shakeOffsetY;
    static float shakeMagnitude;
    static float shakeDuration;
    static sf::Clock shakeClock;

public:
    // Call this to trigger screen shake
    static void triggerShake(float magnitude, float duration) {
        shakeMagnitude = magnitude;
        shakeDuration = duration;
        shakeClock.restart();
    }

    // Call this every frame to update shake effect
    static void updateShake(float deltaTime) {
        if (shakeDuration > 0.0f) {
            float elapsed = shakeClock.getElapsedTime().asSeconds();
            if (elapsed < shakeDuration) {
                float progress = elapsed / shakeDuration;
                float currentMagnitude = shakeMagnitude * (1.0f - progress);

                // Random offsets with decay
                shakeOffsetX = (rand() % 200 - 100) / 100.0f * currentMagnitude;
                shakeOffsetY = (rand() % 200 - 100) / 100.0f * currentMagnitude;
            }
            else {
                // Reset when shake ends
                shakeDuration = 0.0f;
                shakeOffsetX = 0.0f;
                shakeOffsetY = 0.0f;
            }
        }
    }

    // Apply to any view (call before drawing shaken objects)
    static void applyShake(sf::View& view) {
        view.move(shakeOffsetX, shakeOffsetY);
    }

    // Reset a view after applying shake (call after drawing)
    static void resetView(sf::View& view, const sf::RenderWindow& window) {
        view = window.getDefaultView();
    }
};

// Initialize static members
float Effects::shakeOffsetX = 0.0f;
float Effects::shakeOffsetY = 0.0f;
float Effects::shakeMagnitude = 0.0f;
float Effects::shakeDuration = 0.0f;
sf::Clock Effects::shakeClock;
