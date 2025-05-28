#pragma once
#include "Shotgun.hpp"
#include "Enemy.hpp"
#include "Equipement.hpp"

class Player
{
	private :
		Shotgun m_Shotgun;
		sf::Text m_Text;
		sf::CircleShape m_Circle;
		Armor m_Armor;
		AmmoStash m_AmmoStash;
		sf::String infinite = L"\u221E"; //Either put on the texture or move to an other file
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		float m_InputTimer = 0.f;
		int m_Life = 3;
		int m_MaxAmmo = 5;
		int m_BuckShot = 5;
		int m_DragonBreath = 5;
		int m_Slug = 5;
		bool m_CanMove = false;
		bool m_CanReload = true;

	public :
		Player();
		~Player() = default;

		void Init(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock, Armor& _armor, AmmoStash& _ammoStash);

		inline const sf::Vector2f& GetPos() { return this->m_Position; };
		inline const sf::Vector2f& GetVel() { return this->m_Velocity; };
		inline const int GetHP() { return this->m_Life; };

		void Update(EnemyList& _enemyList, TileMap& _map, Window& _window);
		void Display(Window& _window);

		void ModifyShotgun(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock);
		void Equip(Armor& _armor, AmmoStash& _ammoStash);

		bool CheckDamage();

		void Ready();
		void Die();
		void Respawn();
};