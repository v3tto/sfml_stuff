#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "spiral", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    sf::Clock timer;
    float interval = 0.01f; // seconds between frames

    // shape base
    const float radius = 40.f;
    sf::CircleShape baseShape(radius, 5);
    baseShape.setFillColor(sf::Color::Transparent);
    baseShape.setOutlineThickness(-1.f);
    baseShape.setOutlineColor(sf::Color(11, 94, 101));
    baseShape.setOrigin({radius, radius});

    // spiral params
    float a = 0.f;
    float b = 4.f;
    float theta = 0.f;
    float angle_step = 0.1f;

    // vector for storing shapes
    std::vector<sf::CircleShape> shapes;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (timer.getElapsedTime().asSeconds() >= interval)
        {
            // new position
            float r = a + b * theta;
            float x = 400.f + r * std::cos(theta);
            float y = 400.f + r * std::sin(theta);

            // create new shape
            sf::CircleShape shape = baseShape;
            shape.setPosition({x, y});
            shape.setRotation(sf::radians(theta));

            // save in vector
            shapes.push_back(shape);

            theta += angle_step;
            timer.restart();
        }

        window.clear(sf::Color::Black);

        for (const auto &shape : shapes)
            window.draw(shape);

        window.display();
    }

    return 0;
}

// g++ C:\Users\alber\Desktop\sfml_stuff\spiral\main.cpp -o C:\Users\alber\Desktop\sfml_stuff\spiral\spiral.exe `
//  -IC:/C++Libraries/SFML-3.0.0/include `
//  -LC:/C++Libraries/SFML-3.0.0/lib `
//  -lsfml-graphics -lsfml-window -lsfml-system -O2
