#include "Shotgun.hpp"

//////////////////////////////////////////////////

Shotgun::Shotgun()
{
	this->m_Magazine.clear();
	this->m_MaxCapacity = 4;
}
Shotgun::~Shotgun()
{
	this->m_Magazine.clear();
}

void Shotgun::Load(int _input)
{
	if (this->m_Magazine.size() < this->m_MaxCapacity)
	{
		switch (_input)
		{
			case 1:
				this->m_Magazine.push_back(BirdShot());
				break;
			case 2:
				this->m_Magazine.push_back(BuckShot());
				break;
			case 3:
				this->m_Magazine.push_back(DragonBreath());
				break;
			case 4:
				this->m_Magazine.push_back(Slug());
				break;
		}
	}
}

void Shotgun::Shoot(ProjectileList& _list)
{
	if (!this->m_Magazine.empty())
	{
		this->m_Magazine.front().Shot(_list);
		this->m_Magazine.pop_front();
	}
}

//////////////////////////////////////////////////