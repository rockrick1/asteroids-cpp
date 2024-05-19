#include "Bullet.h"

#include "../entities/Asteroid.h"
#include "../Audio.h"
#include "../Game.h"
#include "../Physics.h"
#include "../SoundNames.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : Entity(position, 0, 2), direction(direction), shape(2),
                                                                lifetime(BULLET_LIFE)
{
}

void Bullet::update(float deltaTime)
{
    position += direction * BULLET_SPEED * deltaTime;

    lifetime -= deltaTime;
    if (lifetime <= 0)
        Game::destroyEntity(this);

    for (size_t i = 0; i < Game::getActiveEntities().size(); i++)
    {
        if (typeid(*Game::getActiveEntities()[i]) != typeid(Asteroid))
            continue;

        auto asteroid = dynamic_cast<Asteroid*>(Game::getActiveEntities()[i]);

        if (physics::intersects(position, physics::getTransformedPolygon(asteroid->vertexes, asteroid->getTransform())))
        {
            lifetime = 0;
            Game::destroyEntity(asteroid);
            Game::incrementScore(SCORE_PER_ASTEROID);
            Audio::playSound(ASTEROID_HIT);
            return;
        }
    }
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(shape, getTransform());
}
