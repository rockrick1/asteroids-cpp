﻿#include "Player.h"

#include "Asteroid.h"
#include "Audio.h"
#include "Bullet.h"
#include "Game.h"
#include "Global.h"
#include "Physics.h"
#include "SoundNames.h"

Player::Player() : Entity(sf::Vector2f(500, 500), 0, PLAYER_COLLISION_SIZE / 2), vertexes(sf::LineStrip, 5),
                   shootTimer(0)
{
    vertexes[0].position = sf::Vector2f(PLAYER_SIZE, 0);
    vertexes[1].position = sf::Vector2f(-PLAYER_SIZE, -PLAYER_SIZE);
    vertexes[2].position = sf::Vector2f(-PLAYER_SIZE / 2, 0);
    vertexes[3].position = sf::Vector2f(-PLAYER_SIZE, PLAYER_SIZE);
    vertexes[4].position = vertexes[0].position;

    for (size_t i = 0; i < vertexes.getVertexCount(); i++)
    {
        vertexes[i].color = sf::Color::White;
    }
}

void Player::update(float deltaTime)
{
    if (shootTimer > 0)
        shootTimer -= deltaTime;

    float radians = rotation * DEG_TO_RAD;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotation -= TURN_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotation += TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position.x += cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += sin(radians) * PLAYER_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0)
    {
        Audio::playSound(SHOOT);
        shootTimer = SHOOT_DELAY;
        Game::createEntity(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
    }

    position.x = std::min(std::max(position.x, PLAYER_COLLISION_SIZE / 2), SCREEN_WIDTH - PLAYER_COLLISION_SIZE / 2);
    position.y = std::min(std::max(position.y, PLAYER_COLLISION_SIZE / 2), SCREEN_HEIGHT - PLAYER_COLLISION_SIZE / 2);

    for (size_t i = 0; i < Game::entities.size(); i++)
    {
        if (typeid(*Game::entities[i]) != typeid(Asteroid))
            continue;

        if (physics::intersects(*this, *Game::entities[i]))
        {
            Game::gameOver();
            return;
        }
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(vertexes, getTransform());
}
