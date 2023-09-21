#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::CircleShape smoke_1(30);
    smoke_1.setPosition({540, 185});
    smoke_1.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));

    sf::CircleShape smoke_2(35);
    smoke_2.setPosition({555, 135});
    smoke_2.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));

    sf::CircleShape smoke_3(40);
    smoke_3.setPosition({585, 85});
    smoke_3.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));

    sf::CircleShape smoke_4(45);
    smoke_4.setPosition({605, 35});
    smoke_4.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));

    sf::RectangleShape room;
    room.setSize({600, 350});
    room.setPosition({150, 500});
    room.setFillColor(sf::Color(0x4D, 0x2E, 0x0B));
    
    sf::RectangleShape door;
    door.setSize({100, 250});
    door.setPosition({200, 600});
    door.setFillColor(sf::Color(0x18, 0x17, 0x17));

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x5D, 0x1E, 0x17));
    roof.setPosition({ 50, 300 });
    roof.setPointCount(4);
    roof.setPoint(0, {250, 0});
    roof.setPoint(1, {550, 0});
    roof.setPoint(2, {800, 200});
    roof.setPoint(3, {0, 200});
    
    sf::RectangleShape chimney_1;
    chimney_1.setSize({90, 55});
    chimney_1.setPosition({510, 240});
    chimney_1.setFillColor(sf::Color(0x3B, 0x38, 0x38));

    sf::RectangleShape chimney_2;
    chimney_2.setSize({50, 95});
    chimney_2.setPosition({530, 295});
    chimney_2.setFillColor(sf::Color(0x3B, 0x38, 0x38));
    
    sf::RenderWindow window(sf::VideoMode({900, 870}), "Home sweet home");
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(room);
    window.draw(door);
    window.draw(roof);
    window.draw(smoke_1);    
    window.draw(smoke_2);    
    window.draw(smoke_3);    
    window.draw(smoke_4);    
    window.draw(chimney_1);
    window.draw(chimney_2);
    window.display();

    sf::sleep(sf::seconds(5));
}