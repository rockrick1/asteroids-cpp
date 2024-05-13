#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace physics
{
    bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);
    bool intersects(Entity& e1, Entity& e2);
    float getDistanceSquaredTo(sf::Vector2f& p1, sf::Vector2f& p2);
    float getDistanceTo(sf::Vector2f& p1, sf::Vector2f& p2);
    sf::VertexArray getTransformedPolygon(const sf::VertexArray& polygon, const sf::Transform transform);
}