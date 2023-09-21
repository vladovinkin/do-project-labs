#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({100, 300}), "Traffic light");

    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    sf::RectangleShape base;
    base.setSize({86, 264});
    base.setPosition({14, 18});
    base.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(base);

    sf::CircleShape green_light(36);
    green_light.setPosition({21, 30});
    green_light.setFillColor(sf::Color(0x0, 0x8D, 0xF));
    window.draw(green_light);

    sf::CircleShape yellow_light(36);
    yellow_light.setPosition({21, 116});
    yellow_light.setFillColor(sf::Color(0xFF, 0xCC, 0x26));
    window.draw(yellow_light);

    sf::CircleShape red_light(36);
    red_light.setPosition({21, 202});
    red_light.setFillColor(sf::Color(0xE2, 0x0, 0x0));
    window.draw(red_light);

    window.display();

    sf::sleep(sf::seconds(5));
}