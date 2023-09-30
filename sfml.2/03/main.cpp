#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void processEvent(sf::RenderWindow &window);

int main()
{
    constexpr int pointCount = 20;
    constexpr float circleRadius = 200;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ellipse");

    sf::ConvexShape shape;
    shape.setPosition({400, 320});
    shape.setFillColor(sf::color(0xFF, 0xFF, 0xFF));

    shape.setPointCount(pointCount);
    for(int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCoint);
        sf::Vector2f point = sf::Vector2f{
            circleRadius * std::sin(angle),
            circleRadius * std::cos(angle)
        };
        shape.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        processEvent(window);   
        
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

void processEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}