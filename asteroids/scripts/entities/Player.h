#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

constexpr float PLAYER_SIZE = 15;
constexpr float PLAYER_COLLISION_SIZE = 40;
constexpr float PLAYER_ACCELLERATION = .12f;
constexpr float TURN_SPEED = 250;
constexpr float SHOOT_DELAY = .2f;

class Player : public Entity
{
private:
    sf::VertexArray vertexes;
    sf::Vector2f motion;
    float shootTimer;

public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    void processInputs(float deltaTime);
    void checkDeath();
};
