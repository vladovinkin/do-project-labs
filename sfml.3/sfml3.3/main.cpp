#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::Vector2f position;
    float rotation = 0;
    sf::ConvexShape shape;
    sf::ConvexShape apple;
};

sf::Vector2f toEuclidean(float radius, float angle);
float toDegrees(float radians);
void initEyes(Eye &eyeL, Eye &eyeR);
void update(const sf::Vector2f &mousePosition, Eye &eyeL, Eye &eyeR);
void redrawFrame(sf::RenderWindow &window, Eye eye1, Eye eye2, sf::Vector2f mousePosition);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr int pointCount = 200;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye eyeLeft;
    Eye eyeRight;
    sf::Vector2f mousePosition;

    initEyes(eyeLeft, eyeRight);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyeLeft, eyeRight);
        redrawFrame(window, eyeLeft, eyeRight, mousePosition);
    }
}

// ѕереводит пол€рные координаты в декартовы.
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * float(cos(angle)),
        radius * float(sin(angle))};
}

// ѕереводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void initEyes(Eye &eyeL, Eye &eyeR)
{
    constexpr int pointCount = 200;

    const sf::Vector2f eyeRadius = {80.f, 160.f};
    const sf::Vector2f appleRadius = {20.f, 40.f};

    eyeL.position = {280, 300};
    eyeR.position = {520, 300};

    eyeL.shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeL.shape.setPointCount(pointCount);
    eyeR.shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeR.shape.setPointCount(pointCount);

    eyeL.apple.setFillColor(sf::Color(0x88, 0x44, 0x00));
    eyeL.apple.setPointCount(pointCount);
    eyeR.apple.setFillColor(sf::Color(0x88, 0x44, 0x00));
    eyeR.apple.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f pointEye = {
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        sf::Vector2f pointApple = {
            appleRadius.x * std::sin(angle),
            appleRadius.y * std::cos(angle)};
        eyeL.apple.setPoint(pointNo, pointApple);
        eyeR.apple.setPoint(pointNo, pointApple);
        eyeL.shape.setPoint(pointNo, pointEye);
        eyeR.shape.setPoint(pointNo, pointEye);
    }

    eyeL.shape.setPosition(eyeL.position);
    eyeR.shape.setPosition(eyeR.position);
}

// ќбновл€ет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye &eyeL, Eye &eyeR)
{
    const sf::Vector2f maxAppleRadius = {60.f, 120.f};
    const sf::Vector2f deltaL = mousePosition - eyeL.position;
    const sf::Vector2f deltaR = mousePosition - eyeR.position;

    eyeL.rotation = atan2(deltaL.y, deltaL.x);
    sf::Vector2f posAppleL = {
        maxAppleRadius.x * std::cos(eyeL.rotation),
        maxAppleRadius.y * std::sin(eyeL.rotation)};

    if (abs(deltaL.x) <= abs(posAppleL.x) && abs(deltaL.y) <= abs(posAppleL.y))
    {
        eyeL.apple.setPosition(mousePosition);
    }
    else
    {
        eyeL.apple.setPosition(posAppleL + eyeL.position);
    }

    eyeR.rotation = atan2(deltaR.y, deltaR.x);
    sf::Vector2f posAppleR = {
        maxAppleRadius.x * std::cos(eyeR.rotation),
        maxAppleRadius.y * std::sin(eyeR.rotation)};

    if (abs(deltaR.x) <= abs(posAppleR.x) && abs(deltaR.y) <= abs(posAppleR.y))
    {
        eyeR.apple.setPosition(mousePosition);
    }
    else
    {
        eyeR.apple.setPosition(posAppleR + eyeR.position);
    }
}

// –исует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye eyeL, Eye eyeR, sf::Vector2f mousePosition)
{
    window.clear();
    window.draw(eyeL.shape);
    window.draw(eyeR.shape);
    window.draw(eyeL.apple);
    window.draw(eyeR.apple);
    window.display();
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

// ќпрашивает и обрабатывает доступные событи€ в цикле.
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