#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::Vector2u windowResolution = {windowWidth, windowHeight};
    sf::Vector2f windowCenter = {windowWidth / 2, windowHeight / 2};
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowResolution), "shape_rotation", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    float radius = 1.f;
    float radius_step = 5.f;
    float theta = 0.f;
    float angle_step = 0.1f;

    sf::CircleShape basePentagon(radius, 5);
    basePentagon.setOrigin({radius, radius});
    basePentagon.setPosition(windowCenter);
    basePentagon.setFillColor(sf::Color::Transparent);
    basePentagon.setOutlineThickness(-1.f);
    const int rA = 0;
    const int gA = 0;
    const int bA = 255;
    const int rB = 255;
    const int gB = 0;
    const int bB = 0;

    std::vector<sf::CircleShape> pentagons;
    const int max_pentagons = 210;
    int pentagons_count = 0;

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
                    radius = 1.f;
                    theta = 0.f;
                    pentagons_count = 0;
                    pentagons.clear();
                    std::cout << "Pattern restarted." << std::endl;
                }
            }
        }

        if (pentagons_count < max_pentagons)
        {
            sf::CircleShape pentagon = basePentagon;
            pentagon.setOrigin({radius, radius});
            pentagon.setRadius(radius);
            pentagon.setRotation(sf::radians(theta));
            float t = static_cast<float>(pentagons_count) / max_pentagons;
            int r = (1 - t) * rA + t * rB;
            int g = (1 - t) * gA + t * gB;
            int b = (1 - t) * bA + t * bB;
            pentagon.setOutlineColor(sf::Color(r, g, b));
            pentagons.push_back(pentagon);

            radius += radius_step;
            theta += angle_step;
            pentagons_count++;
            std::cout << "Total of pentagons rendered: " << pentagons_count << std::endl;
        }

        window.clear(sf::Color::Black);

        for (const auto &pentagon : pentagons)
            window.draw(pentagon);

        window.display();
    }

    return 0;
}