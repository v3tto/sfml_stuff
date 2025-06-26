#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "scale_stuff", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(30);

    sf::Clock timer;
    float interval = 0.1f; // seconds between frames

    // shape
    const float radius = 10.f;
    sf::CircleShape shape(radius, 5);
    // color
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(-1.f);
    shape.setOutlineColor(sf::Color(11, 94, 101));
    // position
    shape.setOrigin({radius, radius});
    shape.setPosition({400.f, 400.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // window.clear(sf::Color::Black);

        if (timer.getElapsedTime().asSeconds() >= interval)
        {
            shape.scale({1.05f, 1.05f});
            window.draw(shape);
            timer.restart();
        }
        shape.rotate(sf::degrees(1));
        window.display();
    }

    return 0;
}