#pragma once

#include "Shell.hpp"

class Shotgun
{
	private :
		std::vector<std::unique_ptr<Shell>> m_Magazine;
		int m_MaxCapacity;
	public :
		Shotgun();
		~Shotgun();

		void DisplayMagazine(Window& _window);

		void Load(int _input);
		void Shoot(ProjectileList& _list, sf::Vector2f& _playerpos);
};