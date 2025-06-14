#include "StateManager.hpp"

int main()
{
	srand(unsigned int(time(nullptr)));

	for (int i = 0; i < 25; i++)
	{
		std::cout << Tools::Random(2, -1) * 90.f << std::endl;
	}

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

		if (/*statemana.WindowHasFocus()*/ true)
		{
			statemana.Update();
			statemana.Display();
		}
		else
		{
			Time::Restart();
		}
	}

	return 42;
}