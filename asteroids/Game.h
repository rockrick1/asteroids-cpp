#pragma once
#include <list>
#include <vector>
#include "Entity.h"

constexpr float ASTEROID_SPAWN_INTERVAL = 3;

class Game
{
private:
    static float asteroidSpawnTimer;
    
public:
    static void begin();
    static void update(sf::RenderWindow& window, float deltaTime);
    static void destroyEntity(Entity* entity);
    
    static std::vector<Entity*> entities;
    static std::list<Entity*> entitiesToAdd;
    static std::list<std::vector<Entity*>::const_iterator> entitiesToRemove;
};
