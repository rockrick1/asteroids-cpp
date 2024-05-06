#include "Bullet.h"

#include "Asteroid.h"
#include "Game.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : Entity(position, 0), direction(direction), shape(2), lifetime(BULLET_LIFE) { }

void Bullet::update(float deltaTime)
{
    position += direction * BULLET_SPEED * deltaTime;
    
    lifetime -= deltaTime;
    if (lifetime <= 0)
        Game::destroyEntity(this);

    for (size_t i = 0; i < Game::entities.size(); i++)
    {
        if (typeid(*Game::entities[i]) != typeid(Asteroid))
            continue;
        
        Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);
        const sf::VertexArray& polygon = asteroid->vertexes;
        sf::Transform asteroidTransform = sf::Transform().translate(asteroid->position).rotate(asteroid->rotation);

        size_t n = polygon.getVertexCount() - 1;
        size_t intersectionCount = 0;
        sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), position.y);

        for (size_t j = 0; j < n; j++)
        {
            sf::Vector2f p1 = asteroidTransform.transformPoint(polygon[j].position);
            sf::Vector2f p2 = asteroidTransform.transformPoint(polygon[(j + 1) % n].position);

            if ((p1.y >= position.y || p2.y < position.y) && (p2.y >= position.y || p1.y < position.y))
                continue;
            
            float t = (position.y - p1.y) / (p2.y - p1.y);
            float intersectX = p1.x + t * (p2.x - p1.x);

            if (intersectX <= position.x && intersectX <= rayEnd.x)
                intersectionCount++;
        }

        if (intersectionCount % 2 == 1)
        {
            Game::destroyEntity(asteroid);
            lifetime = 0;
        }
    }
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(shape, sf::Transform().translate(position));
}
