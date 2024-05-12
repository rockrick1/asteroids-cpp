#include "AsteroidSpawner.h"

#include <random>

#include "Global.h"
#include "Game.h"
#include "Physics.h"

AsteroidSpawner::AsteroidSpawner() : Entity(sf::Vector2f(0, 0), 0, 0), spawnTimer(ASTEROID_SPAWN_INTERVAL) { }

void AsteroidSpawner::update(float deltaTime)
{
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0)
    {
        Game::createEntity(new Asteroid(getRandomPosition(), getRandomDirection()));
        spawnTimer = ASTEROID_SPAWN_INTERVAL;
    }
}

void AsteroidSpawner::draw(sf::RenderWindow& window)
{
}

sf::Vector2f AsteroidSpawner::getRandomDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0, 2 * PI);
        
    float angle = distribution(gen);
    return {cos(angle), sin(angle)};
}

sf::Vector2f AsteroidSpawner::getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDistribution(ASTEROID_COLLISION_SIZE / 2, SCREEN_WIDTH - ASTEROID_COLLISION_SIZE / 2);
    std::uniform_real_distribution<float> yDistribution(ASTEROID_COLLISION_SIZE / 2, SCREEN_HEIGHT - ASTEROID_COLLISION_SIZE / 2);

    sf::Vector2f result;
    do
    {
        result = {xDistribution(gen), yDistribution(gen)};
    }
    while (physics::getDistanceSquaredTo(Game::player->position, result) < PLAYER_MINIMUM_SPAWN_DISTANCE_SQUARED);
    return result;
}