#pragma once
#include "Tile.hpp"

class Astar
{
	private :
		std::list<sf::Vector2f> m_Visited;
		std::list<sf::Vector2f> m_Path;
		sf::Vector2f m_Start;
		sf::Vector2f m_Destination;
	public :
		Astar();
		~Astar();
};