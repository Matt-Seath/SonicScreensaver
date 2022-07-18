#include <SFML/Graphics.hpp>
#include <time.h>
#include "animation.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 900), "RT Gaming Test", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    srand(time(NULL));

    sf::Texture texture;
    texture.loadFromFile("sonic.png");
    sf::Sprite sprite(texture);

    Animation animation(&texture, sf::Vector2u(8, 1), 0.3f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    //randomly choose starting point of sprite
    int x =  100;
    int y =  100;
    
    sf::Vector2f shapePosition(x, y);
    sprite.setPosition(shapePosition);

    float xVelocity = 2.0f;
    float yVelocity = 2.0f;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        
        // movements
        shapePosition.x += xVelocity;
        shapePosition.y += yVelocity;

        if (shapePosition.x < 0 || shapePosition.x > window.getSize().x - sprite.getLocalBounds().width + 5)
            xVelocity = -xVelocity;
        if (shapePosition.y < 0 || shapePosition.y > window.getSize().y - sprite.getLocalBounds().height + 20)
            yVelocity = -yVelocity;

        sprite.setPosition(shapePosition);
        animation.Update(0, deltaTime);
        sprite.setTextureRect(animation.uvRect);

        window.clear(sf::Color::Blue);
        window.draw(sprite);
        window.display();
    }
    return 0;
}