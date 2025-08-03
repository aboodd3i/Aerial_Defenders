#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "PirateChicken.h"
#include "KamikazeChicken.h"
#include "Effects.h"
#include "HealthPowerUp.h"

void resetGame(Player& player, Enemy* enemies[], int& enemyCount, int& score, int& health) {
    player.reset();
    for (int i = 0; i < enemyCount; ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemyCount = 0;
    score = 0;
    health = 3;

}

int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 800), "AERIAL DEFENDERS");
    window.setFramerateLimit(60);
        
    // Load background for level 1 (daytime)
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Background_Day.png")) {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }
    sf::Sprite bgSprite(bgTexture);
    sf::Sprite bgSprite2(bgTexture);
	bgSprite.setPosition(0, 0);
    bgSprite2.setPosition(800,0);

    // Load background for level 2 (nighttime)
    sf::Texture bgTextureNight;
    if (!bgTextureNight.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Background_Night.png")) {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }
    sf::Sprite bgSprite3(bgTextureNight);
    sf::Sprite bgSprite4(bgTextureNight);
    bgSprite.setPosition(0, 0);
    bgSprite2.setPosition(800, 0);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Orbitron/Orbitron-VariableFont_wght.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }

    //audio setup
    sf::SoundBuffer chicken_dyingbuffer;
    chicken_dyingbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Chicken_Dying.wav");
    if (!chicken_dyingbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Chicken_Dying.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound chicken_dying;
    chicken_dying.setBuffer(chicken_dyingbuffer);

    sf::SoundBuffer egg_collisionbuffer;
    if (!egg_collisionbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Egg_Cracking.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound egg_collision;
    egg_collision.setBuffer(egg_collisionbuffer);


    sf::SoundBuffer backgroundbuffer;
    backgroundbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Game_Music.wav");
    if (!backgroundbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Game_Music.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound background;
    background.setBuffer(backgroundbuffer);

    sf::SoundBuffer background2buffer;
    if (!background2buffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Game_Music.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound background2;
    background2.setBuffer(backgroundbuffer);


    sf::SoundBuffer bulletbuffer;
    bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Shooting.wav");
    if (!bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Shooting.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound bullet;
    bullet.setBuffer(bulletbuffer);

    background.setLoop(true);
    background.play();
    background.setVolume(80);
    chicken_dying.setVolume(40);

    background2.setLoop(true);
    background2.play();
    background2.setVolume(80);

    sf::SoundBuffer transitionbuffer;
    transitionbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Transition_Sound.wav");
    if (!transitionbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/Transition_Sound.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    
    sf::Sound transition;
    transition.setBuffer(transitionbuffer);



    sf::Clock transitionClock;
    float fadeAlpha = 0.0f;
    bool transitionSoundPlayed = false;

    // Score and UI
    int score = 0, health = 3;
    sf::Text scoreText, lifeText, gameOverText, finalScoreText, restartText, levelclearText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    lifeText.setFont(font);
    lifeText.setCharacterSize(20);
    lifeText.setFillColor(sf::Color::White);
    lifeText.setPosition(10, 40);

    levelclearText.setFont(font);
    levelclearText.setCharacterSize(48);
    levelclearText.setFillColor(sf::Color::Green);
    levelclearText.setString("GAME CLEARED");
    levelclearText.setPosition(400, 250);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(450, 280);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(28);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(500, 355);

    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setString("Press R to Restart");
    restartText.setPosition(485, 400);


    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/HitPoints.png")) {
        std::cout << "Failed to load heart image!" << std::endl;
        return -1;
    }
    sf::Sprite hearts[3];
    for (int i = 0; i < 3; ++i) {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.1f, 0.1f);
        hearts[i].setPosition(10 + i * 35, 70);
    }

    // Game entities
    Player player;
    Enemy* enemies[50];
    PirateChicken* pirateChickens[30];
    KamikazeChicken* kamikazeChicken[20]; // array for kamikaze 
    HealthPowerUp healthPowerUp;

    int pirateCount = 0;
    int enemyCount = 0;
    int kamikazeCount = 0;

    sf::Clock enemySpawnClock;
    sf::Clock pirateSpawnClock;
    sf::Clock kamikazeSpawnClock;
    sf::Clock healthPowerUpClock;

    bool isGameOver = false;

    enum GameState { LEVEL1, TRANSITION_TO_LEVEL2, LEVEL2 };
    GameState gameState = LEVEL1;
    sf::Clock deltaClock;


    // GAME LOOP

    while (window.isOpen()) {
        float backgroundScrollSpeed = 2.0f;
        float deltaTime = deltaClock.restart().asSeconds();

        // Update screen shake effect
        Effects::updateShake(deltaTime);

        if (gameState == LEVEL1) {

            // Temporarily add at start of game loop:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                healthPowerUp.resetPosition();
                healthPowerUp.activate();
            }

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    background.stop();
                    resetGame(player, enemies, enemyCount, score, health);
                    isGameOver = false;
                    enemySpawnClock.restart();
                }
            }

            // Check if player collides with any enemies
            for (int i = 0; i < enemyCount; ++i) {
                if (isGameOver) { break; }
                if (player.getBounds().intersects(enemies[i]->getBounds())) {
                    health--;
                    if (health == 0) {
                        background.stop();
                        isGameOver = true;
                    }
                    delete enemies[i];
                    enemies[i] = enemies[enemyCount - 1];
                    enemies[enemyCount - 1] = nullptr;
                    enemyCount--;
                }
            }
            //check score
            if (score >= 100) {
                background.stop();
                gameState = TRANSITION_TO_LEVEL2;
            }

            // Collision: Player and enemy bullets

            for (int i = 0; i < enemyCount; ++i) {
                if (!enemies[i]) continue;
                if (isGameOver) { break; }

                Bullet** enemyBullets = enemies[i]->getBullets();
                for (int j = 0; j < 10; ++j) {
                    if (isGameOver) { break; }
                    if (!enemyBullets[j]) continue;

                    if (player.getBounds().intersects(enemyBullets[j]->getBounds())) {
                        egg_collision.play();
                        delete enemyBullets[j];

                        for (int k = j; k < 9; ++k) {
                            enemyBullets[k] = enemyBullets[k + 1];
                            if (isGameOver) { break; }
                        }
                        enemyBullets[9] = nullptr;
                        health--;
                        Effects::triggerShake(10.0f, 1.0f); // screen shake

                        if (health <= 0) {
                            isGameOver = true;
                            background.stop();
                            finalScoreText.setString("Final Score: " + std::to_string(score));
                            window.draw(gameOverText);
                            window.draw(finalScoreText);
                            window.draw(restartText);
                            window.display();
                            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                                resetGame(player, enemies, enemyCount, score, health);
                                isGameOver = false;
                                enemySpawnClock.restart();

                            }
                        }
                        break;
                    }
                }
            }

            if (!isGameOver) {
                // Player controls
                player.move();
                player.shoot();
                bullet.play();
                player.updateBullets();

                // Spawn enemies
                if (enemySpawnClock.getElapsedTime().asSeconds() > 2.0f && enemyCount < 50) {
                    if (isGameOver) { break; }
                    float x = 1200; // Right side of screen
                    float y = static_cast<float>(rand() % 550); // Random Y
                    enemies[enemyCount++] = new Enemy(x, y);
                    enemySpawnClock.restart();
                }

                // Update and draw enemies
                for (int i = 0; i < enemyCount; ++i) {
                    if (isGameOver) { break; }
                    enemies[i]->update();
                    enemies[i]->updateBullets();
                    if (enemies[i]->isOffScreen()) {
                        delete enemies[i];
                        enemies[i] = enemies[--enemyCount];
                        enemies[enemyCount] = nullptr;
                        i--;
                    }
                }

                // Bullet-enemy collision

                for (int i = 0; i < player.getBulletCount(); ++i) {
                    Bullet** bullets = player.getBullets();
                    if (!bullets[i]) continue;
                    for (int j = 0; j < enemyCount; ++j) {
                        if (enemies[j] && bullets[i]->getBounds().intersects(enemies[j]->getBounds())) {
                            player.removeBullet(i);
                            delete enemies[j];
                            chicken_dying.play();
                            enemies[j] = enemies[--enemyCount];
                            enemies[enemyCount] = nullptr;
                            score += 10;
                            i--;
                            break;
                        }
                    }
                }

                // Enemy-player collision
                for (int i = 0; i < enemyCount; ++i) {
                    if (isGameOver) { break; }
                    if (player.getBounds().intersects(enemies[i]->getBounds())) {
                        health--;
                        if (health == 0)
                            isGameOver = true;
                        delete enemies[i];
                        enemies[i] = enemies[--enemyCount];
                        enemies[enemyCount] = nullptr;
                        i--;
                    }
                }

                // Move background LEFT (negative X direction for a right-to-left scroll)
                bgSprite.move(-3, 0);  // Negative X to scroll left
                bgSprite2.move(-3, 0);

                // Reset position when background moves fully off-screen LEFT
                if (bgSprite.getPosition().x + bgSprite.getGlobalBounds().width <= 0) {
                    bgSprite.setPosition(bgSprite2.getPosition().x + bgSprite2.getGlobalBounds().width, 0);
                }
                if (bgSprite2.getPosition().x + bgSprite2.getGlobalBounds().width <= 0) {
                    bgSprite2.setPosition(bgSprite.getPosition().x + bgSprite.getGlobalBounds().width, 0);
                }

                // power up stuff:
                healthPowerUp.update(health); // Update position every frame
              
                if (health < 3 && healthPowerUpClock.getElapsedTime().asSeconds() > 10.0f) {
                    healthPowerUp.resetPosition();
                    healthPowerUp.activate();
                    healthPowerUpClock.restart();
                }

                if (healthPowerUp.isActive() && healthPowerUp.checkCollision(player.getBounds())) {
                    if (health < 3) {
                        health++;
                        player.triggerGlow();
                        healthPowerUp.deactivate(); // Disappear after collection
                        healthPowerUp.resetPosition();
                    }
                }

                player.updateGlow();

                // RENDERING  --> abhi na dekhna
                sf::View gameView = window.getDefaultView();

                // Apply shake to view
                Effects::applyShake(gameView);
                window.setView(gameView);
                window.clear();
                window.draw(bgSprite);
                window.draw(bgSprite2);

                player.draw(window);
                player.drawBullets(window);


                for (int i = 0; i < enemyCount; ++i) {
                    if (isGameOver) { break; }
                    enemies[i]->draw(window);
                    enemies[i]->drawBullets(window);
                }

                healthPowerUp.draw(window);

                for (int i = 0; i < health; ++i)
                    window.draw(hearts[i]);

                scoreText.setString("Score: " + std::to_string(score));
                lifeText.setString("Lives: " + std::to_string(health));
                window.draw(scoreText);
                window.draw(lifeText);

                if (isGameOver) {
                    finalScoreText.setString("Final Score: " + std::to_string(score));
                    window.draw(gameOverText);
                    window.draw(finalScoreText);
                    window.draw(restartText);
                }

                // Reset view when done
                Effects::resetView(gameView, window);
                window.setView(gameView);
                window.display();
            }
        }

        else if (gameState == TRANSITION_TO_LEVEL2) {
            if (!transitionSoundPlayed)
            {
                background.stop();
                transition.play();
                transitionSoundPlayed = true;
                transitionClock.restart();
            }

            backgroundScrollSpeed += 85.0f * deltaTime;

            // Scroll backgrounds
            bgSprite.move(backgroundScrollSpeed* deltaTime, 0.0f);
            bgSprite2.move(backgroundScrollSpeed* deltaTime, 0.0f);

            // If backgrounds move out of screen, reset 
            if (bgSprite.getPosition().x >= 1253)
            {
                bgSprite.setPosition(0.0f, bgSprite2.getPosition().x - bgSprite.getGlobalBounds().width); 
            }
            if (bgSprite2.getPosition().x >= 1253)
            {
                bgSprite2.setPosition(0.0f, bgSprite.getPosition().x - bgSprite2.getGlobalBounds().width);
            }

            // Move spaceship rightward
            player.getSprite().move(8.0f, 0.0f);

            // After 2.5 seconds, start fade out
            if (transitionClock.getElapsedTime().asSeconds() > 2.5f)
            {
                fadeAlpha += 55.0f * deltaTime;
                if (fadeAlpha >= 255.0f)
                {
                    fadeAlpha = 255.0f;

                    // Transition complete
                    gameState = LEVEL2;

                    // Reset things
                    backgroundScrollSpeed = 2.0f;
                    player.getSprite().setPosition(10.0f, 250.0f); // (example start pos for Level 2)
                    //transitionSoundPlayed = false;
                    fadeAlpha = 0.0f;
                }
            }

            // RENDERING
            // Get default view
            sf::View gameView = window.getDefaultView();

            // Apply shake to view
            Effects::applyShake(gameView);
            window.setView(gameView);
            if (bgSprite.getPosition().x >= 1200) bgSprite.setPosition(-1200, 0);
            if (bgSprite2.getPosition().x >= 1200) bgSprite2.setPosition(-1200, 0);
            window.clear();
            window.draw(bgSprite);
            window.draw(bgSprite2);
            window.draw(player.getSprite());

            // Fade-out black rectangle
            sf::RectangleShape fadeRect(sf::Vector2f(1200, 800)); // your window size
            fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
            window.draw(fadeRect);

            // Reset view when done
            Effects::resetView(gameView, window);
            window.setView(gameView);

            window.display();
        }

        else if (gameState == LEVEL2) {
            window.clear();
            window.draw(bgSprite3);
            window.draw(bgSprite4);
            background.play();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    background.stop();
                    resetGame(player, enemies, enemyCount, score, health);
                    isGameOver = false;
                    enemySpawnClock.restart();
                }
            }
            if (score >= 200) { // winning game
                isGameOver = true;
                window.draw(levelclearText);
                window.draw(finalScoreText);
                background.stop();
                window.display();
                window.close();

            }

            float bgHeight = bgSprite3.getTexture()->getSize().y;

            // Move background LEFT (negative X direction for a right-to-left scroll)
            bgSprite3.move(-3, 0);  // Negative X to scroll left
            bgSprite4.move(-3, 0);

            // Reset position when background moves fully off-screen LEFT
            if (bgSprite3.getPosition().x + bgSprite3.getGlobalBounds().width <= 0) {
                bgSprite3.setPosition(bgSprite4.getPosition().x + bgSprite4.getGlobalBounds().width, 0);
            } 
            if (bgSprite4.getPosition().x + bgSprite4.getGlobalBounds().width <= 0) {
                bgSprite4.setPosition(bgSprite3.getPosition().x + bgSprite3.getGlobalBounds().width, 0);
            }

            player.draw(window);
            player.drawBullets(window);
            player.move();
            player.shoot();
            player.updateBullets();

            sf::Texture heartTexture;
            if (!heartTexture.loadFromFile("C:/Users/Choudry Shb/source/repos/aerial_defenders_summer_25/assets/HitPoints.png")) {
                std::cout << "Failed to load heart image!" << std::endl;
                return -1;
            }

            // spawining pirate chickens
            if (pirateSpawnClock.getElapsedTime().asSeconds() > 3.0f && pirateCount < 10) {
                pirateChickens[pirateCount++] = new PirateChicken(1200, rand() % 550);  // random Y position, fixed x position
                pirateSpawnClock.restart();
            }
            for (int i = 0; i < pirateCount; ++i) {
                if (pirateChickens[i]) {
                    pirateChickens[i]->draw(window);
                    pirateChickens[i]->update();
                    pirateChickens[i]->updateBullets();
                    pirateChickens[i]->drawBullets(window);
                }
            }

            // spawning kamikaze chicken
            if (kamikazeSpawnClock.getElapsedTime().asSeconds() > 7.0f && kamikazeCount < 10) {
                kamikazeChicken[kamikazeCount++] = new KamikazeChicken(1200, rand() % 300);
                kamikazeSpawnClock.restart();
            }
            for (int i = 0; i < kamikazeCount; i++) {
                if (kamikazeChicken[i]) {
                    kamikazeChicken[i]->draw(window);
                    kamikazeChicken[i]->update();
                }
            }

            // player_bullet - enemy collision
            for (int i = 0; i < pirateCount; ++i) {
                if (!pirateChickens[i] && !kamikazeChicken[i]) continue;
                for (int j = player.getBulletCount() - 1; j >= 0; --j) {
                    Bullet* b = player.getBullets()[j];
                    if (b && pirateChickens[i]->getBounds().intersects(b->getBounds())) {
                        if (pirateChickens[i]->takeHit()) {
                            chicken_dying.play();
                            score += 10;
                            scoreText.setString("Score: " + std::to_string(score));
                            window.draw(scoreText);
                            delete pirateChickens[i];
                            pirateChickens[i] = pirateChickens[--pirateCount];
                            pirateChickens[pirateCount] = nullptr;
                            --i; // re-check current index
                        }
                        player.removeBullet(j);
                        break;
                    }
                }
            }

            //enemy_bullet-player collision
            for (int i = 0; i < pirateCount; ++i) {
                if (!pirateChickens[i]) continue;
                if (isGameOver) { break; }

                Bullet** enemyBullets = pirateChickens[i]->getBullets();
                for (int j = 0; j < 10; ++j) {
                    if (isGameOver) { break; }
                    if (!enemyBullets[j]) continue;

                    if (player.getBounds().intersects(enemyBullets[j]->getBounds())) {
                        egg_collision.play();
                        delete enemyBullets[j];

                        for (int k = j; k < 9; ++k) {
                            enemyBullets[k] = enemyBullets[k + 1];
                            if (isGameOver) { break; }
                        }
                        enemyBullets[9] = nullptr;
                        health--;
                        Effects::triggerShake(12.0f, 1.1f); // strong screen shake

                        if (health <= 0) {
                            isGameOver = true;
                            background.stop();
                            finalScoreText.setString("Final Score: " + std::to_string(score));
                            window.draw(gameOverText);
                            window.draw(finalScoreText);
                            window.draw(restartText);
                            window.display();

                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed)
                                    window.close();
                                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                                    background.stop();
                                    resetGame(player, enemies, enemyCount, score, health);
                                    isGameOver = false;
                                    enemySpawnClock.restart();
                                }
                            }
                        }
                        break;
                    }
                }
            }

            //enemy-player collision
            for (int i = 0; i < pirateCount; i++) {
                if (isGameOver) { break; }
                if (player.getBounds().intersects(pirateChickens[i]->getBounds())) {
                    health--;
                    Effects::triggerShake(12.0f, 1.1f); 
                    if (health == 0)
                        isGameOver = true;
                    delete pirateChickens[i];
                    pirateChickens[i] = pirateChickens[--pirateCount];
                    pirateChickens[pirateCount] = nullptr;
                    i--;
                }            
            }

            for (int i = 0; i < kamikazeCount; i++) {
                if (player.getBounds().intersects(kamikazeChicken[i]->getBounds())) {
                    health--;
                    Effects::triggerShake(12.0f, 1.1f); // screen shake
                    if (health == 0) {
                        isGameOver = true;
                    }
                    delete kamikazeChicken[i];
                    kamikazeChicken[i] = kamikazeChicken[--kamikazeCount];
                    kamikazeChicken[kamikazeCount] = nullptr;
                    i--;
                }
            }

            // power up stuff:
            healthPowerUp.update(health); // Update position every frame

            if (health < 3 && healthPowerUpClock.getElapsedTime().asSeconds() > 10.0f) {
                healthPowerUp.resetPosition();
                healthPowerUp.activate();
                healthPowerUpClock.restart();
            }

            if (healthPowerUp.isActive() && healthPowerUp.checkCollision(player.getBounds())) {
                if (health < 3) {
                    health++;
                    player.triggerGlow();
                    healthPowerUp.deactivate(); // Disappear after collection
                    healthPowerUp.resetPosition();
                }
            }

            player.updateGlow();

			// RENDERING
            sf::View gameView = window.getDefaultView();

            // Apply shake to view
            Effects::applyShake(gameView);
            window.setView(gameView);

            healthPowerUp.draw(window);

            for (int i = 0; i < 3; ++i) {
                hearts[i].setTexture(heartTexture);
                hearts[i].setScale(0.1f, 0.1f);
                hearts[i].setPosition(10 + i * 35, 70);
            }
            for (int i = 0; i < health; ++i)
                window.draw(hearts[i]);
            scoreText.setString("Score: " + std::to_string(score));
            lifeText.setString("Lives: " + std::to_string(health));
            window.draw(scoreText);
            window.draw(lifeText);

            if (isGameOver) {
                finalScoreText.setString("Final Score: " + std::to_string(score));
                window.draw(gameOverText);
                window.draw(finalScoreText);
                window.draw(restartText);
            }

            Effects::resetView(gameView, window);
            window.setView(gameView);

            window.display();   // displays wverything

        }

    }

    for (int i = 0; i < enemyCount; ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }

	for (int i = 0; i < pirateCount; ++i) {
		delete pirateChickens[i];
		pirateChickens[i] = nullptr;
	}

    enemyCount = 0;
    pirateCount = 0;
    return 0;
}
