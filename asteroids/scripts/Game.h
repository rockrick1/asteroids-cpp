#pragma once

#include "entities/Entity.h"
#include "entities/Player.h"
#include "scenes/Scene.h"

constexpr int SCORE_PER_ASTEROID = 1000;
constexpr int TARGET_FPS = 60;
constexpr float FIXED_DELTA_TIME = 1.f / 60.f;

const auto backgroundColor = sf::Color(10, 10, 10, 255);

class Game
{
public:
    static size_t score;
    static size_t highScore;
    static Player* player;
    static sf::Font font;

    static void run();
    static void createEntity(Entity* entity);
    static void destroyEntity(Entity* entity);
    static void incrementScore(int amount);
    static void resetScore();
    static bool updateHighScore();
    static std::vector<Entity*> getActiveEntities();
    static void changeScene(Scene* scene);

private:
    static void initialize();
    static void update(float deltaTime);
};
