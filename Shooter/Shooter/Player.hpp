#pragma once
#include "Tools.hpp"
#include "Window.hpp"

class Player
{
	private :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		int m_Life;
		bool m_CanMove;
		bool m_CanReload;
	public :
		Player();
		~Player();

		inline sf::Vector2f& GetPos() { return this->m_Position; };
		inline sf::Vector2f& GetVel() { return this->m_Velocity; };

		void Update(float _deltatime);
		void Display(Window& _window);

		void Ready();
		void Die();
		void Respawn();
};