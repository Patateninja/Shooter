#pragma once
#include "Window.hpp"
#include "Player.hpp"

class Bonus
{
	protected :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
	public :
		Bonus(sf::Vector2f _pos);
		~Bonus();

		void Update(Player& _player);
		void Display(Window& _window);

		virtual void Collected(Player& _player);
};

class Medkit : public Bonus
{
	public :
		void Collected(Player& _player) override;
};

class XP : public Bonus
{
	public :
		void Collected(Player& _player) override;
};

class AmmoBox : public Bonus
{
	public :
		void Collected(Player& _player) override;
};