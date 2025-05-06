#pragma once
#include "Window.hpp"

class Enemies
{
	protected :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		int m_Life;
		bool m_Active;
	private :
		Enemies();
		~Enemies();

		void Spawn(const sf::Vector2f& _Pos);

		void Move();
		
};