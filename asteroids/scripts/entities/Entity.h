#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    sf::Vector2f position;
    float rotation;
    float size;

    Entity(sf::Vector2f position, float rotation, float size);

    virtual void start();
    virtual void update(float deltaTime);
    virtual void fixedUpdate(float deltaTime);
    virtual void onDestroy();
    virtual void draw(sf::RenderWindow& window);
    sf::Transform getTransform();
    sf::Vector2f getPosition();
};
