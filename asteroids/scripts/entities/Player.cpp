#include "Player.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "../Audio.h"
#include "../Game.h"
#include "../Global.h"
#include "../Physics.h"
#include "../SoundNames.h"
#include "../scenes/GameOverScene.h"

Player::Player() : Entity(sf::Vector2f(500, 500), 0, PLAYER_COLLISION_SIZE / 2), vertexes(sf::LineStrip, 5),
                   motion(sf::Vector2f(0, 0)), shootTimer(0)
{
    vertexes[0].position = sf::Vector2f(PLAYER_SIZE, 0);
    vertexes[1].position = sf::Vector2f(-PLAYER_SIZE, -PLAYER_SIZE);
    vertexes[2].position = sf::Vector2f(-PLAYER_SIZE / 2, 0);
    vertexes[3].position = sf::Vector2f(-PLAYER_SIZE, PLAYER_SIZE);
    vertexes[4].position = vertexes[0].position;

    for (size_t i = 0; i < vertexes.getVertexCount(); i++)
        vertexes[i].color = sf::Color::White;
}

void Player::update(float deltaTime)
{
    processInputs(deltaTime);
    checkDeath();
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(vertexes, getTransform());
}

void Player::processInputs(float deltaTime)
{
    if (shootTimer > 0)
        shootTimer -= deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotation -= TURN_SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotation += TURN_SPEED * deltaTime;

    float radians = rotation * DEG_TO_RAD;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        motion.x += cos(radians) * PLAYER_ACCELLERATION * deltaTime;
        motion.y += sin(radians) * PLAYER_ACCELLERATION * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0)
    {
        Audio::playSound(SHOOT);
        shootTimer = SHOOT_DELAY;
        Game::createEntity(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
    }

    position.x += motion.x;
    position.y += motion.y;

    if (position.x < -PLAYER_COLLISION_SIZE / 2)
        position.x = SCREEN_WIDTH + PLAYER_COLLISION_SIZE / 2;
    if (position.x > SCREEN_WIDTH + PLAYER_COLLISION_SIZE / 2)
        position.x = -PLAYER_COLLISION_SIZE / 2;
    if (position.y < -PLAYER_COLLISION_SIZE / 2)
        position.y = SCREEN_HEIGHT + PLAYER_COLLISION_SIZE / 2;
    if (position.y > SCREEN_HEIGHT + PLAYER_COLLISION_SIZE / 2)
        position.y = -PLAYER_COLLISION_SIZE / 2;
}

void Player::checkDeath()
{
    for (size_t i = 0; i < Game::getActiveEntities().size(); i++)
    {
        if (typeid(*Game::getActiveEntities()[i]) != typeid(Asteroid))
            continue;

        if (physics::intersects(*this, *Game::getActiveEntities()[i]))
            Game::changeScene(new GameOverScene);
    }
}
