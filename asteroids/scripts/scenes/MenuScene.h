﻿#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
    void load() override;
    void update(float deltaTime, float fixedDeltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
