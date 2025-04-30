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
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
			//list.Add(sf::Vector2f(0.f, 0.f), Tools::Normalize(mousePos) * 500.f, CLASSIC, 5, 800);
			list.Add(sf::Vector2f(0.f, 0.f), Tools::AngleToVector(500.f,Tools::VectorToAngle(mousePos)), CLASSIC, 5, 800);
		}

		list.Update(deltatime);
		list.Display(window);

		window.display();
	}

	return 42;
}