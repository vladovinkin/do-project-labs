#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_SIZE = 40;

void processEvent(sf::RenderWindow &window);

int main()
{
    sf::CircleShape ball(BALL_SIZE);
    
    const sf::Vector2f offset = { 10, 350 };
    sf::Vector2f position = offset;
    float speedX = 100.f;
    
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball X-reflection");
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    
    sf::Clock clock;
    float lastTime = clock.getElapsedTime().asSeconds();
    
    while (window.isOpen())
    {
        processEvent(window);   
        
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        const float dt = time - lastTime;
        lastTime = time;
        
        const float wavePhase = time * float(2 *  M_PI);
        const float x = speedX * dt;
        const float y = amplitudeY * std::sin(wavePhase / periodY);

        position.y = y + offset.y;
        position.x += x;

        speedX = (((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0)) || ((position.x < 0) && (speedX < 0)))
            ? -speedX
            : speedX;

        ball.setPosition(position);
        
        window.clear();
        window.draw(ball);
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