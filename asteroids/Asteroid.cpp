#include "Asteroid.h"

#include <random>

#include "Global.h"

Asteroid::Asteroid() : Entity(sf::Vector2f(600, 300), 0), vertexes(sf::LineStrip, 12)
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

    direction = getRandomDirection();
    position = getRandomPosition();
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

sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0, 2 * PI);
        
    float angle = distribution(gen);
    return {cos(angle), sin(angle)};
}

sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDistribution(ASTEROID_COLLISION_SIZE / 2, SCREEN_WIDTH - ASTEROID_COLLISION_SIZE / 2);
    std::uniform_real_distribution<float> yDistribution(ASTEROID_COLLISION_SIZE / 2, SCREEN_HEIGHT - ASTEROID_COLLISION_SIZE / 2);
        
    return {xDistribution(gen), yDistribution(gen)};
}

