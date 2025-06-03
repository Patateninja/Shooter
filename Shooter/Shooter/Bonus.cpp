#include "Bonus.hpp"

////////////////////////////////////////////////////////

Bonus::Bonus(sf::Vector2f _pos)
{
	this->m_Circle.setPosition(_pos);
	this->m_Circle.setRadius(15.f);
	this->m_Circle.setOrigin(15.f, 15.f);
	this->m_Circle.setFillColor(sf::Color::Magenta);
	this->m_Position = _pos;
}
Bonus::~Bonus()
{

}

void Bonus::Update(Player& _player)
{
	if (Tools::CircleCollision(this->m_Circle.getGlobalBounds(), _player.GetHitbox()))
	{
		this->Collected(_player);
	}
}
void Bonus::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

void Bonus::Collected(Player& _player)
{

}

////////////////////////////////////////////////////////

void Medkit::Collected(Player& _player)
{
	_player.AddHP(1);
}

////////////////////////////////////////////////////////

void XP::Collected(Player& _player)
{
	_player.AddHP(1);
}

////////////////////////////////////////////////////////

void AmmoBox::Collected(Player& _player)
{
	_player.AddHP(1);
}

////////////////////////////////////////////////////////