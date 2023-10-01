#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void processEvent(sf::RenderWindow &window);

int main()
{
    constexpr int pointCountShape = 200;
    constexpr int pointCountPath = 200;

    const float pathRadius = 105.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar rose moving",
        sf::Style::Default, settings
    );

    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        processEvent(window);    

        sf::ConvexShape ellipse;
        ellipse.setFillColor(sf::Color(0xFF, 0x00, 0xFF));

        for(int pointPathNo = 0; pointPathNo < pointCountPath; pointPathNo++)
        {
            float angle = -float(2 * M_PI * pointPathNo) / float(pointCountPath);
            sf::Vector2f point = {
                pathRadius * std::sin(angle),
                pathRadius * std::cos(angle)
            };

            ellipse.setPosition({point.x + 400, point.y + 300});
            ellipse.setPointCount(pointCountShape);
            for(int pointShapeNo = 0; pointShapeNo < pointCountShape; ++pointShapeNo)
            {
                float angle = float(2 * M_PI * pointShapeNo) / float(pointCountShape);
                float ellipseRadius = 200 * std::sin(6 * angle);
                sf::Vector2f point = {
                    ellipseRadius * std::sin(angle),
                    ellipseRadius * std::cos(angle),
                };
                ellipse.setPoint(pointShapeNo, point);
            }
           
            window.clear();            
            window.draw(ellipse);
            window.display();
            sf::sleep(sf::seconds(.01));
        }
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