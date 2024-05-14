#include "Physics.h"

bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon)
{
    size_t n = polygon.getVertexCount() - 1;
    size_t intersectionCount = 0;
    auto rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

    for (size_t j = 0; j < n; j++)
    {
        sf::Vector2f p1 = polygon[j].position;
        sf::Vector2f p2 = polygon[(j + 1) % n].position;

        if ((p1.y >= point.y || p2.y < point.y) && (p2.y >= point.y || p1.y < point.y))
            continue;

        float t = (point.y - p1.y) / (p2.y - p1.y);
        float intersectX = p1.x + t * (p2.x - p1.x);

        if (intersectX <= point.x && intersectX <= rayEnd.x)
            intersectionCount++;
    }

    return intersectionCount % 2 == 1;
}

bool physics::intersects(Entity& e1, Entity& e2)
{
    float sizes = e1.size + e2.size;
    return (sizes * sizes) > getDistanceSquaredTo(e1.position, e2.position);
}

float physics::getDistanceSquaredTo(sf::Vector2f& p1, sf::Vector2f& p2)
{
    float xDist = abs(p1.x - p2.x);
    float yDist = abs(p1.y - p2.y);
    return xDist * xDist + yDist * yDist;
}

float physics::getDistanceTo(sf::Vector2f& p1, sf::Vector2f& p2)
{
    return sqrt(getDistanceSquaredTo(p1, p2));
}

sf::VertexArray physics::getTransformedPolygon(const sf::VertexArray& polygon, const sf::Transform transform)
{
    sf::VertexArray transformed = polygon;

    for (size_t i = 0; i < transformed.getVertexCount(); i++)
        transformed[i].position = transform.transformPoint(transformed[i].position);

    return transformed;
}
