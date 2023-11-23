#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer, float &angleDegree);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &angleDegree);
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer);

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
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock, angleDegree);
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
    angleDegree = 0;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &angleDegree)
{
    
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.display();
}
