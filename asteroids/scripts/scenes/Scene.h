#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../entities/Entity.h"

class Scene
{
public:
    std::vector<Entity*> entities{};

private:
    std::vector<Entity*> entitiesToAdd{};
    std::vector<Entity*> entitiesToRemove{};

public:
    Scene();

    virtual void load();
    virtual void update(float deltaTime);
    virtual void unload();
    virtual void draw(sf::RenderWindow& window);

    void createEntity(Entity* entity);
    void destroyEntity(Entity* entity);
};
