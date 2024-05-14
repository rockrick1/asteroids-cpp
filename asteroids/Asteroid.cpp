#include "Asteroid.h"

#include "Game.h"
#include "Global.h"
#include "Utils.h"

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f direction, int level)
    : Entity(position, 0, ASTEROID_BASE_COLLISION_SIZE * level), direction(direction), level(level)
{
    float minRadius = size / 1.3f;
    float maxRadius = size * 1.3f;
    int nodeAmount = utils::randRangei(9, 12);
    float angleStep = PI * 2 / static_cast<float>(nodeAmount);
    vertexes = sf::VertexArray(sf::LineStrip, nodeAmount);

    for (int i = 0; i < nodeAmount; i++)
    {
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

    if (position.x < size / 2)
        direction.x = abs(direction.x);
    else if (position.x > SCREEN_WIDTH - size / 2)
        direction.x = -abs(direction.x);

    if (position.y < size / 2)
        direction.y = abs(direction.y);
    else if (position.y > SCREEN_HEIGHT - size / 2)
        direction.y = -abs(direction.y);
}

void Asteroid::onDestroy()
{
    if (level <= 1)
        return;
    float angle = utils::randRangef(0, 2 * PI);
    sf::Vector2f newDirection = {cos(angle), sin(angle)};
    float distance = 20;

    Game::createEntity(new Asteroid(position + (newDirection * distance), newDirection, level - 1));
    Game::createEntity(new Asteroid(position - (newDirection * distance), -newDirection, level - 1));
}

void Asteroid::draw(sf::RenderWindow& window)
{
    window.draw(vertexes, getTransform());
}
