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

		virtual void Shot(ProjectileList& _list, sf::Vector2f& _playerpos) = 0;
};

class BirdShot : public Shell
{
	public :
		BirdShot();
		~BirdShot();

		void Shot(ProjectileList& _list, sf::Vector2f& _playerpos) override;
};

class BuckShot : public Shell
{
	public :
		BuckShot();
		~BuckShot();

		void Shot(ProjectileList& _list, sf::Vector2f& _playerpos) override;
};

class DragonBreath : public Shell
{
	public :
		DragonBreath();
		~DragonBreath();

		void Shot(ProjectileList& _list, sf::Vector2f& _playerpos) override;
};

class Slug : public Shell
{
	public :
		Slug();
		~Slug();

		void Shot(ProjectileList& _list, sf::Vector2f& _playerpos) override;
};