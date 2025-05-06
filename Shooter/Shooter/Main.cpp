#include "StateManager.hpp"

int main()
{
	StateManager statemana;
	sf::Event event;

	while (Win::IsOpen())
	{
		while (Win::PollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Win::Close();
			}
		}
		statemana.Update();
		statemana.Display();
	}

	return 42;
}