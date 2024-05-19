#include "MenuScene.h"

#include "GameOverScene.h"
#include "GameScene.h"
#include "../Game.h"

sf::Text highScoreText{};
sf::Text menuText{};
sf::Text playText{};

void MenuScene::load()
{
    Scene::load();

    highScoreText.setFont(Game::font);
    highScoreText.setPosition(sf::Vector2f(40, 20));
    highScoreText.setCharacterSize(SCORE_FONT_SIZE);

    menuText.setFont(Game::font);
    menuText.setPosition(sf::Vector2f(280, 350));
    menuText.setCharacterSize(128);
    menuText.setString("ASTEROIDS");

    playText.setFont(Game::font);
    playText.setPosition(sf::Vector2f(450, 550));
    playText.setCharacterSize(CONTINUE_FONT_SIZE);
    playText.setString("Press enter to begin");

    highScoreText.setString("high score: " + std::to_string(Game::highScore));
}

void MenuScene::update(float deltaTime, float fixedDeltaTime)
{
    Scene::update(deltaTime, fixedDeltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Game::changeScene(new GameScene);
}

void MenuScene::draw(sf::RenderWindow& window)
{
    Scene::draw(window);

    window.draw(highScoreText);
    window.draw(menuText);
    window.draw(playText);
}
