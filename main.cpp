#include <SFML/Graphics.hpp>
#include <time.h>
#include "animation.h"


// Created by Matt Seath for RT Gaming Tech Assessment

// ASSUMPTIONS:
//  Game Window is a fixed size of 1500 x 900px,
//  Game uses SFML library,
//  (0, 0) is top-left of screen,
//  Game logo uses a texture atlas to cycle through animation frames,



bool CanWeContinue()
{
    return true;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 900), "RT Gaming Test", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    srand(time(NULL));

    sf::Texture texture;
    texture.loadFromFile("sonic.png");
    sf::Sprite sprite(texture);

    Animation animation(&texture, sf::Vector2u(8, 1), 0.3f);

    float xVelocity = 2.0f;
    float yVelocity = 2.0f;
    float deltaTime = 0.0f;

    sf::Clock clock;
    bool has_entered = false;

    //randomly choose starting point for sonic off-screen along the y-axis
    int x =  -300;
    int y =  std::rand() % 600;
    
    sf::Vector2f Render(x, y);
    sprite.setPosition(Render);

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Check to see if animation can continue
            if (!CanWeContinue() || event.type == sf::Event::Closed)
                window.close();
        }
        
        // sprite movements
        Render.x += xVelocity;
        Render.y += yVelocity;

        // initially allow sprite to pass the screen bounds to enter the screen
        if (has_entered)
        {
            if (Render.x < 0 || Render.x > window.getSize().x - sprite.getLocalBounds().width + 1)
                xVelocity = -xVelocity;
        }
        if (Render.y < 0 || Render.y > window.getSize().y - sprite.getLocalBounds().height + 1)
        {
            yVelocity = -yVelocity;
            has_entered = true;
        }
        sprite.setPosition(Render);
        animation.Update(0, deltaTime);
        sprite.setTextureRect(animation.uvRect);

        window.clear(sf::Color::Blue);
        window.draw(sprite);
        window.display();
    }
    return 0;
}