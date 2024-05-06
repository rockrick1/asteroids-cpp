#include "Game.h"

#include "Asteroid.h"
#include "Player.h"

std::vector<Entity*> Game::entities{};
std::list<Entity*> Game::entitiesToAdd{};
std::list<std::vector<Entity*>::const_iterator> Game::entitiesToRemove{};

float Game::asteroidSpawnTimer{};

void Game::begin()
{
    entities.push_back(new Player());
}

void Game::update(sf::RenderWindow& window, float deltaTime)
{
    entitiesToAdd.clear();
    entitiesToRemove.clear();

    for (size_t i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
        entities[i]->draw(window);
    }

    for (const auto& entity : entitiesToAdd)
    {
        entities.push_back(entity);
    }
    for (const auto& entity : entitiesToRemove)
    {
        delete* entity;
        entities.erase(entity);
    }
    
    asteroidSpawnTimer -= deltaTime;
    if (asteroidSpawnTimer <= 0)
    {
        entities.push_back(new Asteroid());
        asteroidSpawnTimer = ASTEROID_SPAWN_INTERVAL;
    }
}

void Game::destroyEntity(Entity* entity)
{
    entitiesToRemove.push_back(std::find(Game::entities.begin(), Game::entities.end(), entity));
}
