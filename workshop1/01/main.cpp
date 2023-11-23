#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::ConvexShape &pointer);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer);
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer);
        redrawFrame(window, pointer);
    }
    return 0;
}

void init(sf::ConvexShape &pointer)
{
    // pointer.setPointCount(3);
    // pointer.setPoint(0, { 40, 0 });
    // pointer.setPoint(1, { -20, -20 });
    // pointer.setPoint(2, { -20, 20 });
    // pointer.setPosition({ 400, 300 });
    // pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
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
        case sf::Event::MouseMoved:
            // onMouseMove(event.mouseMove, mousePosition);
            break;
        }
    }
}

void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    // const float angle = atan2(delta.y, delta.x);
    // pointer.setRotation(toDegrees(angle));
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}
