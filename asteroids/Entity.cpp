#include "Entity.h"

Entity::Entity(sf::Vector2f position, float rotation, float size) : position(position), rotation(rotation), size(size) { }

sf::Transform Entity::getTransform()
{
    return sf::Transform().translate(position).rotate(rotation);
}

sf::Vector2f Entity::getPosition()
{
    return getTransform().transformPoint(position);
}
