#pragma once
#include "Asteroid.h"
#include "Entity.h"
#include "Player.h"

constexpr float ASTEROID_SPAWN_INTERVAL = .3;
constexpr float PLAYER_MINIMUM_SPAWN_DISTANCE = PLAYER_COLLISION_SIZE + ASTEROID_COLLISION_SIZE;
constexpr float PLAYER_MINIMUM_SPAWN_DISTANCE_SQUARED = PLAYER_MINIMUM_SPAWN_DISTANCE * PLAYER_MINIMUM_SPAWN_DISTANCE;

class AsteroidSpawner : public Entity
{
private:
    float spawnTimer;
    
public:
    AsteroidSpawner();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    static sf::Vector2f getRandomDirection();

    static sf::Vector2f getRandomPosition();
};
