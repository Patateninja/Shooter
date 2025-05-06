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
				statemana.ChangeState<Quit>();
			}
		}
		statemana.Update();
		statemana.Display();
	}

	return 42;
}