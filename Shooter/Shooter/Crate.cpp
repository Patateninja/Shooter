#include "Crate.hpp"

////////////////////////////////////////////////////////

void Crate::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
}

////////////////////////////////////////////////////////

BoostCrate::BoostCrate(sf::Vector2f _pos, bool _canBeHealth, bool _canBeAmmo)
{
	this->m_Pos = _pos;
	this->m_Rect.setPosition(_pos);

	int rand = Tools::Random(2, 0);
	if (rand == 0 && _canBeHealth)
	{
		//Boost is Medkit
	}
	else if (rand == 1 && _canBeAmmo)
	{
		//Boost is Ammo Box
	}
	else
	{
		//Boost is XP
	}
}

void BoostCrate::Update(Player& _player)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize())
	{
		//Input PopUp

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Activate Boost
		}
	}
}

////////////////////////////////////////////////////////

BonusCrate::BonusCrate(sf::Vector2f _pos)
{
	this->m_Pos = _pos;
	this->m_Rect.setPosition(_pos);

	int rand = Tools::Random(2, 0);
	if (rand == 0)
	{
		//Bonus is Coffee
	}
	else if (rand == 1)
	{
		//Boost is Bulletproof Vest
	}
	else
	{
		//Boost is .50 BMG
	}
}

void BonusCrate::Update(Player& _player)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize())
	{
		//Input PopUp

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Activate Bonus
		}
	}
}

////////////////////////////////////////////////////////