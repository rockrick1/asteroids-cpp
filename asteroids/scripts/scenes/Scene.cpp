#include "Scene.h"

bool willUnloadScene;

Scene::Scene()
{
}

void Scene::load()
{
    willUnloadScene = false;
}

void Scene::update(float deltaTime)
{
    for (size_t i = 0; i < entities.size(); i++)
        entities[i]->update(deltaTime);

    if (willUnloadScene)
    {
        entitiesToAdd.clear();
        for (Entity* entity : entities)
            destroyEntity(entity);
    }

    for (int i = 0; i < entitiesToAdd.size(); i++)
    {
        entitiesToAdd[i]->start();
        entities.push_back(entitiesToAdd[i]);
    }
    entitiesToAdd.clear();

    for (int i = 0; i < entitiesToRemove.size(); i++)
    {
        entitiesToRemove[i]->onDestroy();
        entities.erase(std::find(entities.begin(), entities.end(), entitiesToRemove[i]));
        delete entitiesToRemove[i];
    }
    entitiesToRemove.clear();
}

void Scene::unload()
{
    willUnloadScene = true;
}

void Scene::draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < entities.size(); i++)
        entities[i]->draw(window);
}

void Scene::createEntity(Entity* entity)
{
    entitiesToAdd.push_back(entity);
}

void Scene::destroyEntity(Entity* entity)
{
    entitiesToRemove.push_back(entity);
}
