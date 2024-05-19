#pragma once
#include "Scene.h"

constexpr int GAME_OVER_FONT_SIZE = 128;
constexpr int CONTINUE_FONT_SIZE = 24;

class GameOverScene : public Scene
{
public:
    void load() override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
