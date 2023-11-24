#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <iostream>

struct LaserPointer
{
    sf::Sprite sprite;
    bool isOn;
};

void pollEvents(sf::RenderWindow &, LaserPointer &);
void onMouseClick(const sf::Event::MouseButtonEvent &, LaserPointer &);
bool initSprites(sf::Texture &, sf::Sprite &, sf::Texture &, sf::Sprite &);
void redrawFrame(sf::RenderWindow &, sf::Sprite &, LaserPointer &);
void update(sf::Clock &, sf::Sprite &, LaserPointer &);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Cat move to laser pointer", sf::Style::Default, settings);

    LaserPointer laser;

    laser.isOn = false;
    sf::Texture textureCat;
    sf::Texture textureLaser;
    sf::Sprite spriteCat;
    sf::Clock clock;

    if (initSprites(textureCat, spriteCat, textureLaser, laser.sprite))
    {
        spriteCat.setPosition(sf::Vector2f(20, 300));

        redrawFrame(window, spriteCat, laser);

        while (window.isOpen())
        {
            pollEvents(window, laser);
            if (laser.isOn)
            {
                update(clock, spriteCat, laser);
                redrawFrame(window, spriteCat, laser);
            }
            else
            {
                clock.restart().asSeconds();
            }
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

void update(sf::Clock &clock, sf::Sprite &spriteCat, LaserPointer &laser)
{
    const sf::Vector2f spriteCatPosition = spriteCat.getPosition();
    const sf::Vector2f delta = laser.sprite.getPosition() - spriteCatPosition;
    const float deltaNormal = sqrtf(delta.x * delta.x + delta.y * delta.y);
    const float deltaTime = clock.restart().asSeconds();

    if (deltaNormal > .5)
    {
        const sf::Vector2f direction = delta / deltaNormal;
        const float path = 200.0 * deltaTime;

        spriteCat.setPosition(spriteCatPosition + direction * path);
        spriteCat.setScale((delta.x > 0 ? 1 : -1), 1);
    }
    else
    {
        laser.isOn = false;
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &spriteCat, LaserPointer &laser)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    if (laser.isOn)
        window.draw(laser.sprite);
    window.draw(spriteCat);
    window.display();
}

void pollEvents(sf::RenderWindow &window, LaserPointer &laser)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, laser);
            break;
        }
    }
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, LaserPointer &laser)
{
    laser.sprite.setPosition(sf::Vector2f(event.x, event.y));
    laser.isOn = true;
}

bool initSprites(sf::Texture &textureCat, sf::Sprite &spriteCat, sf::Texture &textureLaser, sf::Sprite &spriteLaser)
{
    if (!textureCat.loadFromFile("cat.png"))
    {
        std::cout << "Error loading cat texture!" << std::endl;
        return false;
    }

    if (!textureLaser.loadFromFile("red_pointer.png"))
    {
        std::cout << "Error loading red pointer texture!" << std::endl;
        return false;
    }

    spriteCat.setTexture(textureCat);
    sf::Rect spriteCatRect = spriteCat.getTextureRect();
    spriteCat.setOrigin({
        static_cast<float>(spriteCatRect.width) / 2,
        static_cast<float>(spriteCatRect.height) / 2,
    });

    spriteLaser.setTexture(textureLaser);
    sf::Rect spriteLaserRect = spriteLaser.getTextureRect();
    spriteLaser.setOrigin({
        static_cast<float>(spriteLaserRect.width) / 2,
        static_cast<float>(spriteLaserRect.height) / 2,
    });

    return true;
}