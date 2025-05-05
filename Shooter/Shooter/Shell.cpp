#include "Shell.hpp"

//////////////////////////////////////////////////

BirdShot::BirdShot()
{
	this->m_Damage = 5;
	this->m_Range = 400;
	this->m_Spread = 50;
	this->m_Pellets = 11;
	this->m_Velocity = 750.f;
}
BirdShot::~BirdShot()
{

}

void BirdShot::Shot(sf::Vector2f& _playerPos)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float angle = Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(sf::Mouse::getPosition())) + Tools::DegToRad((this->m_Spread/2) - ((this->m_Spread / this->m_Pellets) * i));
		ProjList::Add(_playerPos, Tools::AngleToVector(this->m_Velocity, angle), CLASSIC, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

BuckShot::BuckShot()
{
	this->m_Damage = 10;
	this->m_Range = 800;
	this->m_Spread = 25;
	this->m_Pellets = 5;
	this->m_Velocity = 750.f;
}
BuckShot::~BuckShot()
{

}

void BuckShot::Shot(sf::Vector2f& _playerPos)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float angle = Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(sf::Mouse::getPosition())) + Tools::DegToRad((this->m_Spread / 2) - ((this->m_Spread / this->m_Pellets) * i));
		ProjList::Add(_playerPos, Tools::AngleToVector(this->m_Velocity, angle), CLASSIC, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

DragonBreath::DragonBreath()
{
	this->m_Damage = 5;
	this->m_Range = 400;
	this->m_Spread = 25;
	this->m_Pellets = 5;
	this->m_Velocity = 1000.f;
}
DragonBreath::~DragonBreath()
{

}

void DragonBreath::Shot(sf::Vector2f& _playerPos)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float angle = Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(sf::Mouse::getPosition())) + Tools::DegToRad((this->m_Spread / 2) - ((this->m_Spread / this->m_Pellets) * i));
		ProjList::Add(_playerPos, Tools::AngleToVector(this->m_Velocity, angle), FLAMMING, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////

Slug::Slug()
{
	this->m_Damage = 20;
	this->m_Range = 1600;
	this->m_Spread = 0;
	this->m_Pellets = 1;
	this->m_Velocity = 1250.f;
}
Slug::~Slug()
{

}

void Slug::Shot(sf::Vector2f& _playerPos)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float angle = Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(sf::Mouse::getPosition())) + Tools::DegToRad((this->m_Spread / 2) - ((this->m_Spread / this->m_Pellets) * i));
		ProjList::Add(_playerPos, Tools::AngleToVector(this->m_Velocity, angle), PIERCING, this->m_Damage, this->m_Range);
	}
}

//////////////////////////////////////////////////