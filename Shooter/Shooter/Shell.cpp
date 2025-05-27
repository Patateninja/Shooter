#include "Shell.hpp"

//////////////////////////////////////////////////

BirdShot::BirdShot(float _spread, float _range, float _velocity)
{
	this->m_Damage = 2;
	this->m_Range = 400 * _range;
	this->m_Spread = 50 * _spread;
	this->m_Pellets = 25;
	this->m_Velocity = 2000.f * _range;
}

void BirdShot::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((float(this->m_Spread) / float(this->m_Pellets - 1)) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + (spread * _recoil);
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, CLASSIC, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

BuckShot::BuckShot(float _spread, float _range, float _velocity)
{
	this->m_Damage = 10;
	this->m_Range = 800 * _range;
	this->m_Spread = 25 * _spread;
	this->m_Pellets = 5;
	this->m_Velocity = 1500.f * _velocity;
}

void BuckShot::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((float(this->m_Spread) / float(this->m_Pellets - 1)) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + (spread * _recoil);
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, CLASSIC, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

DragonBreath::DragonBreath(float _spread, float _range, float _velocity)
{
	this->m_Damage = 5;
	this->m_Range = 400 * _range;
	this->m_Spread = 25 * _spread;
	this->m_Pellets = 5;
	this->m_Velocity = 1500.f * _velocity;
}

void DragonBreath::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _recoil, Window& _window)
{
	for (int i = 0; i < this->m_Pellets; ++i)
	{
		float spread = Tools::DegToRad((this->m_Spread / 2.f) - ((this->m_Spread / (this->m_Pellets - 1)) * i));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition()))) + (spread * _recoil);
		ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, FLAMMING, this->m_Damage, this->m_Range, PLAYER);
	}
}

//////////////////////////////////////////////////

Slug::Slug(float _spread, float _range, float _velocity)
{
	this->m_Damage = 50;
	this->m_Range = 1600 * _range;
	this->m_Spread = 0 * _spread;
	this->m_Pellets = 1;
	this->m_Velocity = 1000.f * _velocity;
}

void Slug::Shot(sf::Vector2f _playerpos, sf::Vector2f _playerVel, float _recoil, Window& _window)
{
	float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(_playerpos) - _window.RelativePos(sf::Mouse::getPosition())));
	ProjList::Add(_playerpos, Tools::AngleToVector(this->m_Velocity, angle) - _playerVel, PIERCING, this->m_Damage, this->m_Range, PLAYER);
}

//////////////////////////////////////////////////