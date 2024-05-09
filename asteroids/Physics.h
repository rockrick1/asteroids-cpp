#pragma once

#include <SFML/Graphics.hpp>

namespace physics
{
    bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);
    bool intersects(const sf::VertexArray& polygon1, const sf::VertexArray& polygon2);
    sf::VertexArray getTransformedPolygon(const sf::VertexArray& polygon, const sf::Transform transform);
}