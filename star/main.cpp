#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::Vector2u windowResolution = {windowWidth, windowHeight};
    const float center_x = windowWidth / 2;
    const float center_y = windowHeight / 2;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowResolution), "star", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    const float pi = 3.141592653589793f;

    const int num_points = 5;
    const int num_vertices = num_points * 2;

    const float outerRadius = 100.f;
    const float innerRadius = 50.f;

    sf::VertexArray star(sf::PrimitiveType::Lines, num_vertices * 2);

    std::vector<sf::Vector2f> points;
    for (size_t i = 0; i < num_vertices; i++) {
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float angle = i * 2 * pi / num_vertices;
        float x = center_x + radius * std::sin(angle);
        float y = center_y - radius * std::cos(angle);
        sf::Vector2f point = {x, y};
        points.emplace_back(point);
    }
    for (size_t i = 0; i < num_vertices; i++)
    {
        size_t next = (i + 1) % num_vertices;
        star[i * 2].position = points[i];
        star[i * 2 + 1].position = points[next];
        star[i * 2].color = sf::Color::Blue;
        star[i * 2 + 1].color = sf::Color::Blue;
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // if (event->is<sf::Event::KeyPressed>())
            // {
            //     const auto *keyEvent = event->getIf<sf::Event::KeyPressed>();
            //     if (keyEvent->code == sf::Keyboard::Key::R)
            //     {
            //         std::cout << "Pattern restarted." << std::endl;
            //     }
            // }
        }

        window.clear(sf::Color::Black);
        window.draw(star);
        window.display();
    }

    return 0;
}