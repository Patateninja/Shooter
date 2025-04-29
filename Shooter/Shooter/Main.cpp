#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Window", sf::Style::Fullscreen);
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.display();
	}

	return 42;
}