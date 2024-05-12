#include "Asteroid.h"

#include "Global.h"
#include "Utils.h"

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f direction) : Entity(position, 0, ASTEROID_COLLISION_SIZE / 2), direction(direction)
{
    float minRadius = ASTEROID_COLLISION_SIZE / 3;
    float maxRadius = ASTEROID_COLLISION_SIZE / 1.3;
    int nodeAmount = utils::randRangei(9, 12);
    float angleStep = PI * 2 / (float)nodeAmount;
    vertexes = sf::VertexArray(sf::LineStrip, nodeAmount);
    
    for(int i = 0; i < nodeAmount; i++) {
        float targetAngle = angleStep * i;
        float angle = targetAngle + (utils::randRangef(-0.5, 0.5)) * angleStep * 0.25;
        float radius = minRadius + utils::randRangef(0, 1) * (maxRadius - minRadius);
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        vertexes[i].position = sf::Vector2f(x, y);
    }
    
    vertexes[nodeAmount - 1].position = vertexes[0].position;

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

