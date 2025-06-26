#include <SFML\Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({512, 512}), "hi :D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen()) // run the program as long as the window is open, this is called "main loop" or "game loop"
    {
        while (const std::optional event = window.pollEvent()) // checks for all window's events
        {
            if (event->is<sf::Event::Closed>()) // this makes the window to close
                window.close();
        }
    }

    
    return 0;
}