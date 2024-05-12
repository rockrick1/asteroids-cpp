#include "Game.h"

#include "Asteroid.h"
#include "Audio.h"
#include "Player.h"
#include "Global.h"
#include <fstream>

std::vector<Entity*> Game::entities{};
std::vector<Entity*> Game::entitiesToAdd{};
std::vector<Entity*> Game::entitiesToRemove{};

size_t Game::score{};
size_t Game::highScore{};
float Game::asteroidSpawnTimer{};

sf::Text Game::highScoreText{};
sf::Text Game::menuText{};
sf::Text Game::playText{};

sf::Text Game::scoreText{};

sf::Text Game::gameOverText{};
sf::Text Game::continueText{};
sf::Font Game::font{};

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",sf::Style::Close | sf::Style::Titlebar);
sf::Clock gameClock{};

Game::State Game::state{};

void Game::initialize()
{
    Audio::initialize();

    std::ifstream file("score.dat", std::ios::binary | std::ios::in);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }
    
    font.loadFromFile("font.ttf");
    
    highScoreText.setFont(font);
    highScoreText.setPosition(sf::Vector2f(40, 20));
    highScoreText.setCharacterSize(SCORE_FONT_SIZE);
    
    menuText.setFont(font);
    menuText.setPosition(sf::Vector2f(280, 350));
    menuText.setCharacterSize(128);
    menuText.setString("ASTEROIDS");
    
    playText.setFont(font);
    playText.setPosition(sf::Vector2f(450, 550));
    playText.setCharacterSize(CONTINUE_FONT_SIZE);
    playText.setString("Press space to begin");
    
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

    state = MENU;
}

void Game::begin()
{
    state = GAME;
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
        
        Game::update(deltaTime);
        window.display();
    }
}

void Game::update(float deltaTime)
{
    window.clear();

    if (state == MENU)
    {
        highScoreText.setString("high score: " + std::to_string(highScore));
        window.draw(highScoreText);
        window.draw(menuText);
        window.draw(playText);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            begin();
        return;
    }
    
    entitiesToAdd.clear();
    entitiesToRemove.clear();

    for (size_t i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
        entities[i]->draw(window);
    }
    if (state == GAME_OVER)
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

    if (state == GAME_OVER)
    {
        window.draw(gameOverText);
        window.draw(continueText);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            begin();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            state = MENU;
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

void Game::incrementScore(int amount)
{
    score += amount;
}

void Game::gameOver()
{
    state = GAME_OVER;
    if (score > highScore)
    {
        printf("YEEHAW");
        highScore = score;
        std::ofstream file("score.dat", std::ios::binary | std::ios::out);
        if (file.is_open())
        {
            file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
            file.close();
        }
        else
            printf("Failed to write highscore to file!");
    }
}
