#include "SFML/Graphics.hpp"

#include "Projectile.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Window", sf::Style::Default);
	sf::Event event;
	sf::Clock time;
	float spawntimer = 0;

	ProjectileList list;

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

		float deltatime = Tools::GetDeltaTime(time);
		time.restart();

		spawntimer += deltatime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawntimer > 0.2)
		{
			spawntimer = 0;
			list.Add(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 300.f), CLASSIC, 5, 800);
		}

		list.Update(deltatime);
		list.Display(window);

		window.display();
	}

	return 42;
}