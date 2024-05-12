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
    Asteroid(sf::Vector2f position, sf::Vector2f direction);

    void update(float deltaTime) override;
    
    void draw(sf::RenderWindow& window) override;
};
