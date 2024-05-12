#pragma once

#include <vector>

#include "Entity.h"

constexpr float ASTEROID_SPAWN_INTERVAL = 2;
constexpr int SCORE_FONT_SIZE = 48;
constexpr int GAME_OVER_FONT_SIZE = 128;
constexpr int CONTINUE_FONT_SIZE = 24;

class Game
{
public:
    static std::vector<Entity*> entities;
    
private:
    static std::vector<Entity*> entitiesToAdd;
    static std::vector<Entity*> entitiesToRemove;
    static size_t score;
    static size_t highScore;
    static float asteroidSpawnTimer;

    static sf::Text highScoreText;
    static sf::Text menuText;
    static sf::Text playText;
    
    static sf::Text scoreText;
    
    static sf::Text gameOverText;
    static sf::Text continueText;
    
    static sf::Font font;
    
    static enum State { MENU, GAME, GAME_OVER } state;
    
public:
    static void initialize();
    static void begin();
    static void run();
    static void update(float deltaTime);
    static void createEntity(Entity* entity);
    static void destroyEntity(Entity* entity);
    static void incrementScore(int amount);
    static void gameOver();
};
