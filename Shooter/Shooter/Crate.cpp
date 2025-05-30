#include "Crate.hpp"

////////////////////////////////////////////////////////

void Crate::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	if (this->m_PlayerClose)
	{
		_window.Draw(this->m_Text);
	}
}

////////////////////////////////////////////////////////

BoostCrate::BoostCrate(sf::Vector2f _pos, bool _canBeHealth, bool _canBeAmmo)
{
	this->m_Pos = _pos;
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setOrigin(this->m_Rect.getSize() / 2.f);
	this->m_Rect.setFillColor(sf::Color::Red);
	this->m_Text.setPosition(_pos);

	int rand = Tools::Random(2, 0);
	if (rand == 0 && _canBeHealth)
	{
		this->m_Boost = MEDKIT;
	}
	else if (rand == 1 && _canBeAmmo)
	{
		this->m_Boost = AMMOBOX;
	}
	else
	{
		this->m_Boost = XP;
	}
}

void BoostCrate::Update(Player& _player)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize() * 2 && !this->m_Opened)
	{
		this->m_PlayerClose = true;

		//Input PopUp

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->m_Opened = true;
			this->m_Rect.setFillColor(sf::Color::Black);

			switch (this->m_Boost)
			{
				case MEDKIT :
					_player.Heal();
					break;
				case AMMOBOX :
					_player.Refill();
					break;
				case XP :
					Level::GainXP(250);
					break;
				default :
					break;
			}
		}
	}
	else
	{
		this->m_PlayerClose = false;
	}
}

////////////////////////////////////////////////////////

BonusCrate::BonusCrate(sf::Vector2f _pos)
{
	this->m_Pos = _pos;
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setOrigin(this->m_Rect.getSize() / 2.f);
	this->m_Rect.setFillColor(sf::Color::Green);
	this->m_Text.setPosition(_pos);

	int rand = Tools::Random(2, 0);
	if (rand == 0)
	{
		this->m_Bonus = COFFEE;
	}
	else if (rand == 1)
	{
		this->m_Bonus = VEST;
	}
	else
	{
		this->m_Bonus = BMG50;
	}
}

void BoostCrate::Delete()
{
	this->~BoostCrate();
}

void BonusCrate::Update(Player& _player)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize() * 2 && !this->m_Opened)
	{
		this->m_PlayerClose = true;
		
		//Input PopUp

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->m_Opened = true;
			this->m_Rect.setFillColor(sf::Color::Black);

			switch (this->m_Bonus)
			{
				case COFFEE :
					_player.Coffee(true);
					break;
				case VEST :
					_player.AddVest();
					break;
				case BMG50 :
					_player.BMG50(true);
					break;
				default :
					break;
			}
		}	
	}
	else
	{
		this->m_PlayerClose = false;
	}
}

void BonusCrate::Delete()
{
	this->~BonusCrate();
}

////////////////////////////////////////////////////////