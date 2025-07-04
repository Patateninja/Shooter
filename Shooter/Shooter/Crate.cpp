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
	this->m_Rect.setTexture(&RscMana::Get<sf::Texture>("BoostCrate"));
	this->m_Rect.setTextureRect(sf::IntRect(0,0,64,64));
	this->m_Text.setPosition(_pos - sf::Vector2f(this->m_Text.getGlobalBounds().getSize().x / 2.f, this->m_Rect.getSize().y / 2.f + this->m_Text.getGlobalBounds().getSize().y));

	int rand = Tools::Random(2);
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

void BoostCrate::Update(Player& _player, bool& _coffe, bool& _bmg, bool& _vest, BonusPopUp*& _popUp)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize() * 2 && !this->m_Opened)
	{
		this->m_PlayerClose = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->m_Opened = true;
			this->m_Rect.setTextureRect(sf::IntRect(64, 0, 64, 64));
			RscMana::Get<sf::Sound>("CrateOpen").play();

			switch (this->m_Boost)
			{
				case MEDKIT :
					_player.Heal();
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "MedkitPopUp");
					break;
				case AMMOBOX :
					_player.Refill();
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "AmmoPopUp");
					break;
				case XP :
					Level::GainXP(250);
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "XpPopUp");
					break;
				default :
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "Somehow another thing (This is worrysome)", "Placeholder");
					break;
			}
		}
	}
	else
	{
		this->m_PlayerClose = false;
	}
}

void BoostCrate::Delete()
{
	this->~BoostCrate();
}

////////////////////////////////////////////////////////

BonusCrate::BonusCrate(sf::Vector2f _pos)
{
	this->m_Pos = _pos;
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setOrigin(this->m_Rect.getSize() / 2.f);
	this->m_Rect.setTexture(&RscMana::Get<sf::Texture>("BonusCrate"));
	this->m_Rect.setTextureRect(sf::IntRect(0, 0, 64, 64));
	this->m_Text.setPosition(_pos - sf::Vector2f(this->m_Text.getGlobalBounds().getSize().x / 2.f, this->m_Rect.getSize().y / 2.f + this->m_Text.getGlobalBounds().getSize().y));

	int rand = Tools::Random(2);
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

void BonusCrate::Update(Player& _player, bool& _coffee, bool& _bmg, bool& _vest, BonusPopUp*& _popUp)
{
	if (Tools::Distance(this->m_Pos, _player.GetPos()) < Tile::GetSize() * 2 && !this->m_Opened)
	{
		this->m_PlayerClose = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->m_Opened = true;
			this->m_Rect.setTextureRect(sf::IntRect(64, 0, 64, 64));
			RscMana::Get<sf::Sound>("CrateOpen").play();

			switch (this->m_Bonus)
			{
				case COFFEE :
					_coffee = true;
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "CoffeePopUp");
					break;
				case VEST :
					_vest = true;;
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "VestPopUp");
					break;
				case BMG50 :
					_bmg = true;
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "", "BmgPopUp");
					break;
				default :
					_popUp = new BonusPopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "Somehow another thing (This is worrysome)", "Placeholder");
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