#include "Shell.hpp"

//////////////////////////////////////////////////

BirdShot::BirdShot()
{
	this->m_Damage = 5;
	this->m_Range = 400;
	this->m_Spread = 50;
	this->m_Pellets = 11;
	this->m_Velocity = 1000.f;
}
BirdShot::~BirdShot()
{

}

void BirdShot::Shot(sf::Vector2f& _playerpos, sf::Vector2f& _playerVel, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / this->m_Pellets) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + spread;
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, CLASSIC, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

BuckShot::BuckShot()
{
	this->m_Damage = 10;
	this->m_Range = 800;
	this->m_Spread = 25;
	this->m_Pellets = 5;
	this->m_Velocity = 1000.f;
}
BuckShot::~BuckShot()
{

}

void BuckShot::Shot(sf::Vector2f& _playerpos, sf::Vector2f& _playerVel, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / this->m_Pellets) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(_playerpos) -_window.RelativePos(sf::Mouse::getPosition()))) + spread;
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, CLASSIC, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

DragonBreath::DragonBreath()
{
	this->m_Damage = 5;
	this->m_Range = 400;
	this->m_Spread = 25;
	this->m_Pellets = 5;
	this->m_Velocity = 1500.f;
}
DragonBreath::~DragonBreath()
{

}

void DragonBreath::Shot(sf::Vector2f& _playerpos, sf::Vector2f& _playerVel, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / this->m_Pellets) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + spread;
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, FLAMMING, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

Slug::Slug()
{
	this->m_Damage = 50;
	this->m_Range = 1600;
	this->m_Spread = 0;
	this->m_Pellets = 1;
	this->m_Velocity = 2000.f;
}
Slug::~Slug()
{

}

void Slug::Shot(sf::Vector2f& _playerpos, sf::Vector2f& _playerVel, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / this->m_Pellets) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + spread;
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, PIERCING, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////