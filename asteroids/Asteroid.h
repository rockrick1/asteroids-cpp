#pragma once
#include "Entity.h"

constexpr float ASTEROID_ROTATION = 25;
constexpr float ASTEROID_SPEED = 75;
constexpr float ASTEROID_BASE_COLLISION_SIZE = 25;

class Asteroid : public Entity
{
public:
    sf::VertexArray vertexes;
    
private:
    
    sf::Vector2f direction;
    int level;

public:
    Asteroid(sf::Vector2f position, sf::Vector2f direction, int level);

    void update(float deltaTime) override;
    void onDestroy() override;
    void draw(sf::RenderWindow& window) override;
};
