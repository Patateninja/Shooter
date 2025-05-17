#include "Shield.hpp"

Shield::Shield(sf::Vector2f _pos)
{
	this->m_Rect.setSize(sf::Vector2f(5.f, 50.f));
	this->m_Rect.setOrigin(-30.f, 25.f);
	this->m_Rect.setPosition(_pos);
}

void Shield::Udpate(bool _active, sf::Vector2f _pos, float _angle)
{
	this->SetActive(_active);
	this->SetPos(_pos);
	this->SetAngle(_angle);
}

void Shield::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
}