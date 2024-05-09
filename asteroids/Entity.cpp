#include "Entity.h"

Entity::Entity(sf::Vector2f position, float rotation) : position(position), rotation(rotation) { }

sf::Transform Entity::getTransform()
{
    return sf::Transform().translate(position).rotate(rotation);
}
