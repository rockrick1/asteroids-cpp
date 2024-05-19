#pragma once
#include "Scene.h"

constexpr int SCORE_FONT_SIZE = 48;

class GameScene : public Scene
{
public:
    void load() override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
