#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    sf::Vector2f position;
    float rotation;
    
    Entity(sf::Vector2f position, float rotation);
    
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    sf::Transform getTransform();
};
