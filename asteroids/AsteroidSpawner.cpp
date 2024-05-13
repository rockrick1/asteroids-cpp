#include "AsteroidSpawner.h"

#include <random>

#include "Global.h"
#include "Game.h"
#include "Physics.h"
#include "Utils.h"

AsteroidSpawner::AsteroidSpawner() : Entity(sf::Vector2f(0, 0), 0, 0), spawnTimer(ASTEROID_SPAWN_INTERVAL) { }

void AsteroidSpawner::update(float deltaTime)
{
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0)
    {
        Game::createEntity(new Asteroid(getRandomPosition(), getRandomDirection(), ASTEROID_SPAWN_LEVEL));
        spawnTimer = ASTEROID_SPAWN_INTERVAL;
    }
}

sf::Vector2f AsteroidSpawner::getRandomDirection()
{
    float angle = utils::randRangef(0, 2 * PI);
    return {cos(angle), sin(angle)};
}

sf::Vector2f AsteroidSpawner::getRandomPosition()
{
    sf::Vector2f result;
    do
    {
        result = {utils::randRangef(ASTEROID_BASE_COLLISION_SIZE / 2, SCREEN_WIDTH - ASTEROID_BASE_COLLISION_SIZE / 2),
            utils::randRangef(ASTEROID_BASE_COLLISION_SIZE / 2, SCREEN_HEIGHT - ASTEROID_BASE_COLLISION_SIZE / 2)};
    }
    while (physics::getDistanceSquaredTo(Game::player->position, result) < PLAYER_MINIMUM_SPAWN_DISTANCE_SQUARED);
    return result;
}