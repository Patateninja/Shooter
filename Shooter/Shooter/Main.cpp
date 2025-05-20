#include "StateManager.hpp"

int main()
{
	srand(unsigned int(time(nullptr)));

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

		if (statemana.WindowHasFocus())
		{
			statemana.Update();
		}
		else
		{
			Time::Restart();
		}
		statemana.Display();
	}

	return 42;
}