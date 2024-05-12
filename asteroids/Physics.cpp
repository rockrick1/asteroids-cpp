#include "Physics.h"

bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon)
{
    size_t n = polygon.getVertexCount() - 1;
    size_t intersectionCount = 0;
    sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

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

bool physics::intersects(const sf::VertexArray& polygon1, const sf::VertexArray& polygon2)
{
    size_t n1 = polygon1.getVertexCount() - 1;
    size_t n2 = polygon2.getVertexCount() - 1;

    for (size_t i = 0; i < n1; i++)
    {
        sf::Vector2f edge = polygon1[i].position - polygon1[(i + 1) % n1].position;
        sf::Vector2f normal(-edge.y, edge.x);
        
        float length = sqrt(normal.x * normal.x + normal.y * normal.y);
        normal /= length;

        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();

        for (size_t j = 0; j < n1; j++)
        {
            float projection = polygon1[j].position.x * normal.x + polygon1[j].position.y * normal.y;
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (size_t j = 0; j < n2; j++)
        {
            float projection =
                polygon2[j].position.x * normal.x + polygon2[j].position.y * normal.y;
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if (max1 < min2 || max2 < min1)
            return false;
    }

    return true;
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
    return xDist*xDist + yDist*yDist;
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
