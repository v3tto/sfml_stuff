#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    const int windowWidth = 1600;
    const int windowHeight = 900;
    const float center_x = windowWidth / 2;
    const float center_y = windowHeight / 2;
    sf::Vector2u windowResolution = {windowWidth, windowHeight};
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(windowResolution), "fermat's spiral", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    const float pi = 3.141592653589793f;

    const float turn = 2 * pi;
    const float max_theta = 60 * turn;

    float shapeRadius = 15.f;
    float theta = 0.f;
    float angle_step = 0.1f;
    float spacing = 50.f;

    sf::CircleShape baseShape(shapeRadius, 6);
    baseShape.setOrigin({shapeRadius, shapeRadius});
    baseShape.setFillColor(sf::Color::Transparent);
    baseShape.setOutlineThickness(-1.f);

    const int colorA_r = 0;
    const int colorA_g = 0;
    const int colorA_b = 255;

    const int colorB_r = 255;
    const int colorB_g = 0;
    const int colorB_b = 0;

    const int colorC_r = 0;
    const int colorC_g = 255;
    const int colorC_b = 0;

    const int colorD_r = 255;
    const int colorD_g = 0;
    const int colorD_b = 0;

    std::vector<sf::CircleShape> shapes;
    int shapes_drawn = 0;

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
                    theta = 0.f;
                    shapes_drawn = 0;
                    shapes.clear();
                    std::cout << "Pattern restarted." << std::endl;
                }
            }
        }

        if (theta <= max_theta)
        {
            sf::CircleShape shape = baseShape;

            float x = spacing * sqrt(std::abs(theta)) * cos(theta);
            float y = spacing * sqrt(std::abs(theta)) * sin(theta);
            float t = static_cast<float>(theta) / max_theta;

            shape.setPosition({center_x + x, center_y - y});
            shape.setRotation(sf::radians(theta));
            int rA = (1 - t) * colorA_r + t * colorB_r;
            int gA = (1 - t) * colorA_g + t * colorB_g;
            int bA = (1 - t) * colorA_b + t * colorB_b;
            shape.setOutlineColor(sf::Color(rA, gA, bA));
            shapes.push_back(shape);
            shapes_drawn++;

            shape.setPosition({center_x - x, center_y + y});
            shape.setRotation(sf::radians(theta));
            int rB = (1 - t) * colorC_r + t * colorD_r;
            int gB = (1 - t) * colorC_g + t * colorD_g;
            int bB = (1 - t) * colorC_b + t * colorD_b;
            shape.setOutlineColor(sf::Color(rB, gB, bB));
            shapes.push_back(shape);
            shapes_drawn++;

            theta += angle_step;
            std::cout << "Shapes drawn: " << shapes_drawn << std::endl;
        }

        window.clear(sf::Color::Black);
        for (const auto &shape : shapes)
            window.draw(shape);
        window.display();
    }

    return 0;
}