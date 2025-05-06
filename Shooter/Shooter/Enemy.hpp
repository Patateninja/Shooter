#pragma once
#include "Window.hpp"
#include "Projectile.hpp"
#include "ResourceManager.hpp"

class Enemy
{
	protected :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		int m_Hp;
		bool m_Active;
	public :
		Enemy();
		~Enemy();

		void Update(float _deltatime, sf::Vector2f& _playerPos);
		void Display(Window& _window);

		void Move(float _deltatime);
		void TakeDamage();
};