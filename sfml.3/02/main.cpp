#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT}), "Prints mouse events to terminal");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    std::cout << "mouse pressed,"
                              << " x=" << event.mouseButton.x
                              << " y=" << event.mouseButton.y
                              << std::endl;
                    break;
                case sf::Event::MouseButtonReleased:
                    std::cout << "mouse pressed,"
                            << " x=" << event.mouseButton.x
                            << " y=" << event.mouseButton.y
                            << std::endl;
                    break;
            }
        }

        window.clear();
        window.display();
    }
    return 0;
}