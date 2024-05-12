#include "Asteroid.h"

#include <random>

#include "Global.h"

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f direction) : Entity(position, 0, ASTEROID_COLLISION_SIZE / 2), vertexes(sf::LineStrip, 12), direction(direction)
{
    vertexes[0].position = sf::Vector2f(-40, 40);
    vertexes[1].position = sf::Vector2f(-50, 10);
    vertexes[2].position = sf::Vector2f(-10, -20);
    vertexes[3].position = sf::Vector2f(-20, -40);
    vertexes[4].position = sf::Vector2f(10, -40);
    vertexes[5].position = sf::Vector2f(40, -20);
    vertexes[6].position = sf::Vector2f(40, -10);
    vertexes[7].position = sf::Vector2f(10, 0);
    vertexes[8].position = sf::Vector2f(40, 20);
    vertexes[9].position = sf::Vector2f(20, 40);
    vertexes[10].position = sf::Vector2f(0, 30);
    vertexes[11].position = vertexes[0].position;

    for (size_t i = 0; i < vertexes.getVertexCount(); i++)
    {
        vertexes[i].color = sf::Color::White;
    }
}

void Asteroid::update(float deltaTime)
{
    position += ASTEROID_SPEED * direction * deltaTime;
    rotation += ASTEROID_ROTATION * deltaTime;

    if (position.x < ASTEROID_COLLISION_SIZE / 2)
        direction.x = abs(direction.x);
    else if (position.x > SCREEN_WIDTH - ASTEROID_COLLISION_SIZE / 2)
        direction.x = -abs(direction.x);

    if (position.y < ASTEROID_COLLISION_SIZE / 2)
        direction.y = abs(direction.y);
    else if (position.y > SCREEN_HEIGHT - ASTEROID_COLLISION_SIZE / 2)
        direction.y = -abs(direction.y);
}

void Asteroid::draw(sf::RenderWindow& window)
{
    window.draw(vertexes, getTransform());
}

