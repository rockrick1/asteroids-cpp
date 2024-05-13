#pragma once
#include "Asteroid.h"
#include "Entity.h"
#include "Player.h"

constexpr float ASTEROID_SPAWN_INTERVAL = .3f;
constexpr int ASTEROID_SPAWN_LEVEL = 3;
constexpr float PLAYER_MINIMUM_SPAWN_DISTANCE = PLAYER_COLLISION_SIZE + (ASTEROID_BASE_COLLISION_SIZE * ASTEROID_SPAWN_LEVEL);
constexpr float PLAYER_MINIMUM_SPAWN_DISTANCE_SQUARED = PLAYER_MINIMUM_SPAWN_DISTANCE * PLAYER_MINIMUM_SPAWN_DISTANCE;

class AsteroidSpawner : public Entity
{
private:
    float spawnTimer;
    
public:
    AsteroidSpawner();

    void update(float deltaTime) override;

private:
    static sf::Vector2f getRandomDirection();
    static sf::Vector2f getRandomPosition();
};
