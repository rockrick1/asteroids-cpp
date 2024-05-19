#include "GameScene.h"

#include "../Game.h"
#include "../entities/AsteroidSpawner.h"

sf::Text scoreText{};

void GameScene::load()
{
    Scene::load();

    Game::player = new Player;
    entities.push_back(Game::player);
    entities.push_back(new AsteroidSpawner);

    scoreText.setFont(Game::font);
    scoreText.setPosition(sf::Vector2f(30, 20));
    scoreText.setCharacterSize(SCORE_FONT_SIZE);
}


void GameScene::update(float deltaTime, float fixedDeltaTime)
{
    Scene::update(deltaTime, fixedDeltaTime);

    scoreText.setString(std::to_string(Game::score));
}

void GameScene::draw(sf::RenderWindow& window)
{
    Scene::draw(window);

    window.draw(scoreText);
}
