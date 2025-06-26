#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8; // adds antialiasing

    sf::RenderWindow window(sf::VideoMode({600, 200}), "positioning_stuff", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    // circle
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color(22, 90, 76));
    circle.setOrigin({100.f, 100.f});
    circle.setPosition({100.f, 100.f});

    // triangle
    sf::CircleShape triangle(100.f, 3);
    triangle.setFillColor(sf::Color(195, 36, 84));
    triangle.setOrigin({100.f, 100.f});
    triangle.setPosition({300.f, 100.f});

    // hexagon
    sf::CircleShape hexagon(100.f, 6);
    hexagon.setFillColor(sf::Color(77, 155, 230));
    hexagon.setOrigin({100.f, 100.f});
    hexagon.setPosition({500.f, 100.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(triangle);
        window.draw(hexagon);
        circle.rotate(sf::degrees(1));
        triangle.rotate(sf::degrees(1));
        hexagon.rotate(sf::degrees(1));
        window.display();
    }

    return 0;
}