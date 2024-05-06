#include "Game.h"

#include "Asteroid.h"
#include "Audio.h"
#include "Player.h"

std::vector<Entity*> Game::entities{};
std::list<Entity*> Game::entitiesToAdd{};
std::list<std::vector<Entity*>::const_iterator> Game::entitiesToRemove{};

size_t Game::score{};
float Game::asteroidSpawnTimer{};

sf::Text Game::scoreText{};
sf::Font Game::font{};

void Game::begin()
{
    Audio::initialize();
    
    font.loadFromFile("font.ttf");
    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(30, 20));
    scoreText.setCharacterSize(SCORE_FONT_SIZE);
    
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

    scoreText.setString(std::to_string(score));
    window.draw(scoreText);
}

void Game::destroyEntity(Entity* entity)
{
    entitiesToRemove.push_back(std::find(Game::entities.begin(), Game::entities.end(), entity));
}
