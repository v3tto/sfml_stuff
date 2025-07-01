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
    sf::RenderWindow window(sf::VideoMode(windowResolution), "shooting_star_attempt", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    const float pi = 3.141592653589793f;

    const int num_points = 5;
    const int num_vertices = num_points * 2;

    const float outerRadius = 100.f;
    const float innerRadius = 50.f;

    float rotation = 0.f;
    const float angle_step = 0.05f;

    float time = 0.f;

    float trail_length = 0.f;

    sf::VertexArray star(sf::PrimitiveType::Lines, num_vertices * 2);

    sf::VertexArray star_trail = star;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                const auto *keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent->code == sf::Keyboard::Key::R)
                {
                    rotation = 0.f;
                    trail_length = 0.f;
                    std::cout << "Restarted." << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);

        std::vector<sf::Vector2f> points;
        float vertical_offset = 150.f * std::sin(time);
        float horizontal_offset = 50.f * std::cos(time / 3);
        for (size_t i = 0; i < num_vertices; i++)
        {
            float radius = (i % 2 == 0) ? outerRadius : innerRadius;
            float angle = (i * 2 * pi / num_vertices) + rotation;
            float x = (center_x + radius * std::sin(angle) + horizontal_offset);
            float y = (center_y - radius * std::cos(angle) + vertical_offset);
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

        std::vector<sf::Vector2f> trail_points = points;
        for (size_t i = 0; i < num_vertices; i++)
        {
            trail_points[i].x -= trail_length;
            size_t next = (i + 1) % num_vertices;
            star_trail[i * 2].position = trail_points[i];
            star_trail[i * 2 + 1].position = trail_points[next];
            star_trail[i * 2].color = sf::Color::Transparent;
            star_trail[i * 2 + 1].color = sf::Color::Green;
        }

        window.draw(star_trail);
        window.draw(star);

        rotation += angle_step;
        time += 0.05f;
        if (trail_length <= 600)
            trail_length += 5.f;

        window.display();
    }

    return 0;
}