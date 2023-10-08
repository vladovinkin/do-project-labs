#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer, float &angleDegree);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &angleDegree);
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer);
float toDegrees(float radians);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void calcAngle(float angleReal, float &angleDegree, float deltaTime);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse with speed limit", sf::Style::Default, settings);

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
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
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
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        }
    }
}

void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &angleDegree)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = atan2(delta.y, delta.x);
    const float deltaTime = clock.restart().asSeconds();
    const float limitAngle = 15.0 * deltaTime;

    calcAngle(toDegrees(angle), angleDegree, limitAngle);

    pointer.setRotation(angleDegree);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void calcAngle(float angleReal, float &angleDegree, float limitAngle)
{
    float deltaAngle = angleReal - angleDegree;
    if (deltaAngle < -180)
        deltaAngle += 360;
    if (deltaAngle > 180)
        deltaAngle -= 360;

    angleDegree += (deltaAngle > 0)
        ? std::min(deltaAngle, limitAngle)
        : -std::min(-deltaAngle, limitAngle);

    if (angleDegree > 360)
        angleDegree -= 360;
    if (angleDegree < -360)
        angleDegree += 360;
}