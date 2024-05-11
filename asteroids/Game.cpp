#include "Game.h"

#include "Asteroid.h"
#include "Audio.h"
#include "Player.h"
#include "Global.h"

std::vector<Entity*> Game::entities{};
std::vector<Entity*> Game::entitiesToAdd{};
std::vector<Entity*> Game::entitiesToRemove{};

size_t Game::score{};
float Game::asteroidSpawnTimer{};

sf::Text Game::gameOverText{};
sf::Text Game::continueText{};
sf::Text Game::scoreText{};
sf::Font Game::font{};

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",sf::Style::Close | sf::Style::Titlebar);
sf::Clock gameClock{};

bool isGameOver;

void Game::initialize()
{
    Audio::initialize();
    
    font.loadFromFile("font.ttf");
    
    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(30, 20));
    scoreText.setCharacterSize(SCORE_FONT_SIZE);
    
    gameOverText.setFont(font);
    gameOverText.setPosition(sf::Vector2f(250, 350));
    gameOverText.setCharacterSize(GAME_OVER_FONT_SIZE);
    gameOverText.setString("Game Over!");
    
    continueText.setFont(font);
    continueText.setPosition(sf::Vector2f(450, 550));
    continueText.setCharacterSize(CONTINUE_FONT_SIZE);
    continueText.setString("Press space to play again");

    begin();
}

void Game::begin()
{
    isGameOver = false;
    entities.clear();
    score = 0;
    entities.push_back(new Player());
    asteroidSpawnTimer = ASTEROID_SPAWN_INTERVAL;
}

void Game::run()
{
    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        Game::update(deltaTime);
        window.display();
    }
}

void Game::update(float deltaTime)
{
    entitiesToAdd.clear();
    entitiesToRemove.clear();

    for (size_t i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
        entities[i]->draw(window);
    }
    if (isGameOver)
    {
        entitiesToAdd.clear();
        for (Entity* entity : entities)
            destroyEntity(entity);
    }

    for (const auto& entity : entitiesToAdd)
        entities.push_back(entity);
    
    for (int i = 0; i < entitiesToRemove.size(); i++)
    {
        entities.erase(std::find(entities.begin(), entities.end(), entitiesToRemove[i]));
        delete entitiesToRemove[i];
    }

    asteroidSpawnTimer -= deltaTime;
    if (asteroidSpawnTimer <= 0)
    {
        entities.push_back(new Asteroid());
        asteroidSpawnTimer = ASTEROID_SPAWN_INTERVAL;
    }

    scoreText.setString(std::to_string(score));
    window.draw(scoreText);

    if (isGameOver)
    {
        window.draw(gameOverText);
        window.draw(continueText);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            begin();
    }
}

void Game::createEntity(Entity* entity)
{
    entitiesToAdd.push_back(entity);
}

void Game::destroyEntity(Entity* entity)
{
    entitiesToRemove.push_back(entity);
}

void Game::gameOver()
{
    isGameOver = true;
}

void removeEntities()
{
    
}
