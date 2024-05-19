#pragma once
#include "Asteroid.h"
#include "Entity.h"
#include "Player.h"

constexpr int STARTING_LEVEL = 3;
constexpr float SPAWN_INTERVAL = 1;
constexpr float PLAYER_MINIMUM_SPAWN_DISTANCE = PLAYER_COLLISION_SIZE + (ASTEROID_BASE_COLLISION_SIZE * STARTING_LEVEL);

class AsteroidSpawner : public Entity
{
    float spawnTimer;

public:
    AsteroidSpawner();

    void update(float deltaTime) override;

private:
    static sf::Vector2f getRandomDirection();
    static sf::Vector2f getRandomPosition();
};
