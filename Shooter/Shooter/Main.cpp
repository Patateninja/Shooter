#include "StateManager.hpp"

int main()
{
	StateManager statemana;
	sf::Event event;

	while (statemana.WindowIsOpen())
	{
		while (statemana.GetWindow().PollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				statemana.GetWindow().Close();
			}
		}
		statemana.Update();
		statemana.Display();
	}

	return 42;
}