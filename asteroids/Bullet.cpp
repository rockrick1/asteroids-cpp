#include "Bullet.h"

#include "Asteroid.h"
#include "Audio.h"
#include "Game.h"
#include "Physics.h"
#include "SoundNames.h"

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
        sf::Transform asteroidTransform = sf::Transform().translate(asteroid->position).rotate(asteroid->rotation);

        if (physics::intersects(position, physics::getTransformedPolygon(asteroid->vertexes, asteroidTransform)))
        {
            lifetime = 0;
            Game::destroyEntity(asteroid);
            Game::score += 10;
            Audio::playSound(ASTEROID_HIT);
            return;
        }
    }
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(shape, sf::Transform().translate(position));
}
