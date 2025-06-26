#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "draw_stuff");
    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color(220, 20, 60));  // color, `sf::Color::Transparent` for only outline
    shape.setOutlineThickness(10.f);             // default color is white
    shape.setOutlineColor(sf::Color(86, 31, 8)); // outline color

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black); // clear the window with black color, this is mandatory before drawing anything
        window.draw(shape);             // ps dibuja
        shape.move({5.f, 5.f});
        window.display();               // end the current frame, also mandatory
    }
}

// notes:
// Calling display is also mandatory, it takes what was drawn since
// the last call to display and displays it on the window. Indeed,
// things are not drawn directly to the window, but to a hidden buffer.
// This buffer is then copied to the window when you call display
// -- this is called double-buffering.