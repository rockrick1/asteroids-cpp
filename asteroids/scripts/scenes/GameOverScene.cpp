#include "GameOverScene.h"

#include <fstream>

#include "GameScene.h"
#include "MenuScene.h"
#include "../Game.h"

sf::Text gameOverText{};
sf::Text continueText{};

void GameOverScene::load()
{
    Scene::load();

    if (Game::updateHighScore())
    {
        std::ofstream file("score.dat", std::ios::binary | std::ios::out);
        if (file.is_open())
        {
            file.write(reinterpret_cast<const char*>(&Game::highScore), sizeof(size_t));
            file.close();
        }
        else
            printf("Failed to write highscore to file!");
    }
    Game::resetScore();

    gameOverText.setFont(Game::font);
    gameOverText.setPosition(sf::Vector2f(250, 350));
    gameOverText.setCharacterSize(GAME_OVER_FONT_SIZE);
    gameOverText.setString("Game Over!");

    continueText.setFont(Game::font);
    continueText.setPosition(sf::Vector2f(450, 550));
    continueText.setCharacterSize(CONTINUE_FONT_SIZE);
    continueText.setString("Press enter to play again");
}

void GameOverScene::update(float deltaTime, float fixedDeltaTime)
{
    Scene::update(deltaTime, fixedDeltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Game::changeScene(new GameScene);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        Game::changeScene(new MenuScene);
}

void GameOverScene::draw(sf::RenderWindow& window)
{
    Scene::draw(window);

    window.draw(gameOverText);
    window.draw(continueText);
}
