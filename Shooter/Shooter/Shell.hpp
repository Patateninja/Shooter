#pragma once
#include "Projectile.hpp"

class Shell
{
	protected :
		int m_Damage = 0;
		int m_Range = 0;
		int m_Spread = 0;
		int	m_Pellets = 0;
		float m_Velocity = 0;
	public :
		Shell() = default;
		~Shell() = default;

		int GetSpread() { return this->m_Spread; };

		virtual void Shot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _recoil, Window& _window) = 0;
};

class BirdShot : public Shell
{
	public :
		BirdShot(float _spread, float _range, float _velocity);
		~BirdShot();

		void Shot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _recoil, Window& _window) override;
};

class BuckShot : public Shell
{
	public :
		BuckShot(float _spread, float _range, float _velocity);
		~BuckShot();

		void Shot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _recoil, Window& _window) override;
};

class DragonBreath : public Shell
{
	public :
		DragonBreath(float _spread, float _range, float _velocity);
		~DragonBreath();

		void Shot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _recoil, Window& _window) override;
};

class Slug : public Shell
{
	public :
		Slug(float _spread, float _range, float _velocity);
		~Slug();

		void Shot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _recoil, Window& _window) override;
};