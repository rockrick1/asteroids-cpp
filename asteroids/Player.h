﻿#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

constexpr float PLAYER_SIZE = 15;
constexpr float PLAYER_COLLISION_SIZE = 40;
constexpr float PLAYER_SPEED = 150;
constexpr float TURN_SPEED = 250;
constexpr float SHOOT_DELAY = .4f;

class Player : public Entity
{
private:
    sf::VertexArray vertexes;
    
    float shootTimer;
    
public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
