#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Global.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",
        sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;

    Game::begin();

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        Game::update(window, deltaTime);
        
        window.display();
    }
}
