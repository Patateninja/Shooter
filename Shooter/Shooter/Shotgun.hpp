#pragma once

#include "Shell.hpp"

class Shotgun
{
	private :
		std::list<Shell> m_Magazine;
		int m_MaxCapacity;
	public :
		Shotgun();
		~Shotgun();

		void Load(int _input);
		void Shoot(ProjectileList& _list);
};