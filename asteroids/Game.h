#pragma once

#include <list>
#include <vector>

#include "Entity.h"

constexpr float ASTEROID_SPAWN_INTERVAL = 3;
constexpr int SCORE_FONT_SIZE = 48;

class Game
{
public:
    static std::vector<Entity*> entities;
    static std::list<Entity*> entitiesToAdd;
    static std::list<std::vector<Entity*>::const_iterator> entitiesToRemove;
    
    static size_t score;
    
private:
    static float asteroidSpawnTimer;
    static sf::Text scoreText;
    static sf::Font font;
    
public:
    static void begin();
    static void update(sf::RenderWindow& window, float deltaTime);
    static void destroyEntity(Entity* entity);
};
