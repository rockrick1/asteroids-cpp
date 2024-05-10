#pragma once

#include <list>
#include <vector>

#include "Entity.h"

constexpr float ASTEROID_SPAWN_INTERVAL = 2;
constexpr int SCORE_FONT_SIZE = 48;

class Game
{
public:
    static std::vector<Entity*> entities;
    static size_t score;
    
private:
    static std::vector<Entity*> entitiesToAdd;
    static std::vector<Entity*> entitiesToRemove;
    static float asteroidSpawnTimer;
    static sf::Text scoreText;
    static sf::Font font;
    
public:
    static void initialize();
    static void begin();
    static void run();
    static void update(float deltaTime);
    static void createEntity(Entity* entity);
    static void destroyEntity(Entity* entity);
    static void gameOver();
};
