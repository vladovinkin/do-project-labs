#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void processEvent(sf::RenderWindow &window);

int main()
{
    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::CircleShape shape(BALL_SIZE);
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;
    sf::Vector2f speed = { 50.f, 15.f };

    shape.setPosition({200, 120});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    

    while (window.isOpen())
    {
        processEvent(window);   

        const float dt = clock.restart().asSeconds();

        sf::Vector2f position = shape.getPosition();
        position += speed * dt;

        speed.x = (((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0)) || ((position.x < 0) && (speed.x < 0)))
            ? -speed.x
            : speed.x;

        speed.y = (((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0)) || ((position.y < 0) && (speed.y < 0)))
            ? -speed.y
            : speed.y;

        shape.setPosition(position);

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