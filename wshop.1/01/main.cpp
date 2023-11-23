#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &, float &);
void pollEvents(sf::RenderWindow &);
void redrawFrame(sf::RenderWindow &, sf::ConvexShape &);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Draw arrow", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    sf::Clock clock;
    float angleDegree;

    init(pointer, angleDegree);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, pointer);
    }
    return 0;
}

void init(sf::ConvexShape &pointer, float &angleDegree)
{
    pointer.setPointCount(7);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {0, -40});
    pointer.setPoint(2, {0, -20});
    pointer.setPoint(3, {-40, -20});
    pointer.setPoint(4, {-40, 20});
    pointer.setPoint(5, {0, 20});
    pointer.setPoint(6, {0, 40});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0xFD, 0x00));
    pointer.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    pointer.setOutlineThickness(2.0);
    angleDegree = 45;
    pointer.setRotation(angleDegree);
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.display();
}
