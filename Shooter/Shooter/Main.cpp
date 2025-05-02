#include "StateManager.hpp"

int main()
{
	ResourceManager rscmana;
	StateManager statemana(&rscmana);
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