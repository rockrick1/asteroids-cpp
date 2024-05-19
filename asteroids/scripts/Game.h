#pragma once

#include "entities/Entity.h"
#include "entities/Player.h"
#include "scenes/Scene.h"

constexpr int SCORE_PER_ASTEROID = 1000;

const auto backgroundColor = sf::Color(10, 10, 10, 255);

class Game
{
public:
    static size_t score;
    static size_t highScore;
    static Player* player;

private:
    static sf::Text highScoreText;
    static sf::Text menuText;
    static sf::Text playText;

public:
    static sf::Font font;

    static void initialize();
    static void run();
    static void createEntity(Entity* entity);
    static void destroyEntity(Entity* entity);
    static void incrementScore(int amount);
    static void resetScore();
    static bool updateHighScore();
    static std::vector<Entity*> getActiveEntities();
    static void changeScene(Scene* scene);

private:
    static void update(float deltaTime);
};
