#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "moving_stuff_modify", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    sf::Clock timer;
    float interval = 0.05f; // seconds between frames

    // circle 0
    sf::CircleShape circle0(100.f);
    circle0.setFillColor(sf::Color::Transparent);
    circle0.setOutlineThickness(-5.f);
    circle0.setOutlineColor(sf::Color::Red);
    // circle 1
    sf::CircleShape circle1(100.f);
    circle1.setFillColor(sf::Color::Transparent);
    circle1.setOutlineThickness(-5.f);
    circle1.setOutlineColor(sf::Color::Green);
    // circle 2
    sf::CircleShape circle2(100.f);
    circle2.setFillColor(sf::Color::Transparent);
    circle2.setOutlineThickness(-5.f);
    circle2.setOutlineColor(sf::Color::Blue);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (timer.getElapsedTime().asSeconds() >= interval)
        {
            window.draw(circle0);
            window.draw(circle1);
            window.draw(circle2);
            timer.restart();
        }

        circle0.move({5.f, 0.f});
        circle1.move({5.f, 5.f});
        circle2.move({0.f, 5.f});
        window.display();
    }
}