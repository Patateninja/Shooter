#include "Shell.hpp"

//////////////////////////////////////////////////

BirdShot::BirdShot(float _spread, float _range, float _velocity)
{
	this->m_Damage = 2;
	this->m_Range = int(400 * _range);
	this->m_Spread = int(50 * _spread);
	this->m_Pellets = 25;
	this->m_Velocity = 3000.f * _range;
}

void BirdShot::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _playerAngle, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((float(this->m_Spread) / float(this->m_Pellets - 1)) * i));
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, _playerAngle + (spread * _recoil)) - _playerVel, CLASSIC, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

BuckShot::BuckShot(float _spread, float _range, float _velocity)
{
	this->m_Damage = 10;
	this->m_Range = int(800 * _range);
	this->m_Spread = int(25 * _spread);
	this->m_Pellets = 8;
	this->m_Velocity = 2500.f * _velocity;
}

void BuckShot::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _playerAngle, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((float(this->m_Spread) / float(this->m_Pellets - 1)) * i));
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, _playerAngle + (spread * _recoil)) - _playerVel, CLASSIC, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

DragonBreath::DragonBreath(float _spread, float _range, float _velocity)
{
	this->m_Damage = 5;
	this->m_Range = int(400 * _range);
	this->m_Spread = int(25 * _spread);
	this->m_Pellets = 5;
	this->m_Velocity = 2500.f * _velocity;
}

void DragonBreath::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _playerAngle, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / float(this->m_Pellets - 1)) * i));
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, _playerAngle + (spread * _recoil)) - _playerVel, FLAMMING, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

Slug::Slug(float _spread, float _range, float _velocity)
{
	this->m_Damage = 75;
	this->m_Range = int(1600 * _range);
	this->m_Spread = 0;
	this->m_Pellets = 1;
	this->m_Velocity = 2000.f * _velocity;
}

void Slug::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _playerAngle, float _recoil, Window& _window)
{
	ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, _playerAngle) - _playerVel, PIERCING, this->m_Damage, this->m_Range, PLAYER);
}

//////////////////////////////////////////////////

BMG::BMG(float _spread, float _range, float _velocity)
{
	this->m_Damage = 1000;
	this->m_Range = int(10000 * _range);
	this->m_Spread = 0;
	this->m_Pellets = 1;
	this->m_Velocity = 6000.f * _velocity;
}

void BMG::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _playerAngle, float _recoil, Window& _window)
{
	ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, _playerAngle) - _playerVel, PIERCING, this->m_Damage, this->m_Range, PLAYER);
}

//////////////////////////////////////////////////