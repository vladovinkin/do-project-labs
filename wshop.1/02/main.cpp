#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

void init(sf::ConvexShape &, float &);
void pollEvents(sf::RenderWindow &, sf::Vector2f &);
void update(sf::Vector2f &, sf::ConvexShape &, sf::Clock &, float &);
void redrawFrame(sf::RenderWindow &, sf::ConvexShape &);
float toDegrees(float);
void onMouseMove(const sf::Event::MouseMoveEvent &, sf::Vector2f &);
void calcAngle(float, float &, float);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow moves to cursor", sf::Style::Default, settings);

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
    angleDegree = 45;
    pointer.setRotation(angleDegree);
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.display();
}

void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &angleDegree)
{
    const sf::Vector2f pointerPosition = pointer.getPosition();
    const sf::Vector2f delta = mousePosition - pointerPosition;

    const float deltaTime = clock.restart().asSeconds();
    const float deltaNormal = sqrtf(delta.x * delta.x + delta.y * delta.y);

    if (deltaNormal)
    {
        const float angle = atan2(delta.y, delta.x);
        const float limitAngle = 90.0 * deltaTime;
        const sf::Vector2f direction = delta / deltaNormal;
        const float path = 20.0 * deltaTime;
        
        calcAngle(toDegrees(angle), angleDegree, limitAngle);

        pointer.setRotation(angleDegree);
        pointer.setPosition(pointerPosition + direction * path);
    }
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
