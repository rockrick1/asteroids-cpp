#pragma once
#include "Entity.h"

constexpr float ASTEROID_ROTATION = 25;
constexpr float ASTEROID_SPEED = 75;
constexpr float ASTEROID_COLLISION_SIZE = 80;

class Asteroid : public Entity
{
public:
    sf::VertexArray vertexes;
    
private:
    sf::Vector2f direction;
    
public:
    Asteroid();

    void update(float deltaTime) override;
    
    void draw(sf::RenderWindow& window) override;

private:
    static sf::Vector2f getRandomDirection();

    static sf::Vector2f getRandomPosition();
};
