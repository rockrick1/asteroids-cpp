#include "Game.h"

#include "Audio.h"
#include "Global.h"
#include <fstream>

#include "entities/Asteroid.h"
#include "scenes/MenuScene.h"
#include "scenes/Scene.h"

size_t Game::score{};
size_t Game::highScore{};
Player* Game::player;

sf::Font Game::font{};

sf::RenderWindow window(
    sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
    "Asteroids",
    sf::Style::Close | sf::Style::Titlebar
);
sf::Clock gameClock{};

Scene* currentScene = nullptr;

void Game::initialize()
{
    Audio::initialize();
    window.setFramerateLimit(TARGET_FPS);

    std::ifstream file("score.dat", std::ios::binary | std::ios::in);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }

    font.loadFromFile("assets/font.ttf");

    changeScene(new MenuScene);
}

void Game::run()
{
    initialize();
    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear(backgroundColor);
        update(deltaTime);
        window.display();
    }
}

void Game::update(float deltaTime)
{
    currentScene->update(deltaTime, FIXED_FELTA_TIME);
    currentScene->draw(window);
}

void Game::createEntity(Entity* entity)
{
    currentScene->createEntity(entity);
}

void Game::destroyEntity(Entity* entity)
{
    currentScene->destroyEntity(entity);
}

void Game::incrementScore(int amount)
{
    score += amount;
}

void Game::resetScore()
{
    score = 0;
}

bool Game::updateHighScore()
{
    if (highScore >= score)
        return false;
    highScore = score;
    return true;
}

std::vector<Entity*> Game::getActiveEntities()
{
    return currentScene->entities;
}

void Game::changeScene(Scene* scene)
{
    if (currentScene != nullptr)
        currentScene->unload();
    delete currentScene;
    currentScene = scene;
    currentScene->load();
}
