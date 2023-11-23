#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

void pollEvents(sf::RenderWindow &);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Static cat sprite", sf::Style::Default, settings);

    sf::Texture texture;
    if (!texture.loadFromFile("cat.png"))
    {
        std::cout << "Error loading texture!" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(200, 100));

    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(sprite);
    window.display();

    while (window.isOpen())
    {
        pollEvents(window);
    }
    return 0;
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}
