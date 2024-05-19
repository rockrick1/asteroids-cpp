#pragma once
#include "Entity.h"

constexpr float BULLET_SPEED = 400;
constexpr float BULLET_LIFE = 3;

class Bullet : public Entity
{
    sf::Vector2f direction;
    sf::CircleShape shape;
    float lifetime;

public:
    Bullet(sf::Vector2f position, sf::Vector2f direction);

    void update(float deltaTime) override;

    void draw(sf::RenderWindow& window) override;
};
