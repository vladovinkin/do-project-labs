#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({650, 350}), "My initials");

    window.clear(sf::Color(0xAA, 0xAA, 0xAA));

    sf::CircleShape o_1(75);
    o_1.setPosition({50, 50});
    o_1.setFillColor(sf::Color(0x80, 0x40, 0x0));
    window.draw(o_1);

    sf::CircleShape o_2(75);
    o_2.setPosition({50, 150});
    o_2.setFillColor(sf::Color(0x80, 0x40, 0x0));
    window.draw(o_2);
    
    sf::RectangleShape o_3;
    o_3.setSize({150, 100});
    o_3.setPosition({50, 125});
    o_3.setFillColor(sf::Color(0x80, 0x40, 0x0));
    window.draw(o_3);
    
    sf::CircleShape o_4(25);
    o_4.setPosition({100, 100});
    o_4.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));
    window.draw(o_4);
    
    sf::CircleShape o_5(25);
    o_5.setPosition({100, 200});
    o_5.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));
    window.draw(o_5);
    
    sf::RectangleShape o_6;
    o_6.setSize({50, 100});
    o_6.setPosition({100, 125});
    o_6.setFillColor(sf::Color(0xAA, 0xAA, 0xAA));
    window.draw(o_6);

    sf::RectangleShape v_1;
    v_1.setSize({50, 245});
    v_1.setRotation(-11);
    v_1.setOrigin({50, 0});    
    v_1.setPosition({300, 50});
    v_1.setFillColor(sf::Color(0x0, 0xFF, 0x40));
    window.draw(v_1);

    sf::RectangleShape v_2;
    v_2.setSize({50, 245});
    v_2.setRotation(11);
    v_2.setPosition({350, 50});
    v_2.setFillColor(sf::Color(0x0, 0xFF, 0x40));
    window.draw(v_2);

    sf::RectangleShape v_3;
    v_3.setSize({50, 25});
    v_3.setPosition({300, 275});
    v_3.setFillColor(sf::Color(0x0, 0xFF, 0x40));
    window.draw(v_3);

    sf::RectangleShape v_4;
    v_4.setSize({50, 10});
    v_4.setPosition({250, 50});
    v_4.setFillColor(sf::Color(0x0, 0xFF, 0x40));
    window.draw(v_4);

    sf::RectangleShape v_5;
    v_5.setSize({50, 10});
    v_5.setPosition({350, 50});
    v_5.setFillColor(sf::Color(0x0, 0xFF, 0x40));
    window.draw(v_5);

    sf::RectangleShape e_1;
    e_1.setSize({50, 250});
    e_1.setPosition({450, 50});
    e_1.setFillColor(sf::Color(0xFF, 0x80, 0x0));
    window.draw(e_1);

    sf::RectangleShape e_2;
    e_2.setSize({100, 50});
    e_2.setPosition({500, 50});
    e_2.setFillColor(sf::Color(0xFF, 0x80, 0x0));
    window.draw(e_2);

    sf::RectangleShape e_3;
    e_3.setSize({50, 50});
    e_3.setPosition({500, 150});
    e_3.setFillColor(sf::Color(0xFF, 0x80, 0x0));
    window.draw(e_3);

    sf::RectangleShape e_4;
    e_4.setSize({100, 50});
    e_4.setPosition({500, 250});
    e_4.setFillColor(sf::Color(0xFF, 0x80, 0x0));
    window.draw(e_4);

    window.display();

    sf::sleep(sf::seconds(5));
}