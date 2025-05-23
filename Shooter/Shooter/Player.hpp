#pragma once
#include "Shotgun.hpp"
#include "Enemy.hpp"
#include "Equipement.hpp"

class Player
{
	private :
		sf::Text m_Text;
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		sf::String infinite = L"\u221E";
		Shotgun m_Shotgun;
		Armor m_Armor;
		AmmoStash m_AmmoStash;
		float m_InputTimer;
		int m_Life;
		int m_MaxAmmo;
		int m_BuckShot;
		int m_DragonBreath;
		int m_Slug;
		bool m_CanMove;
		bool m_CanReload;
	public :
		Player();
		~Player();

		void ModifyShotgun(Muzzle& _muzzle, Grip _grip, Magazine _magazine, Stock _stock);

		void Equip(Armor& _armor, AmmoStash& _ammoStash);

		inline sf::Vector2f& GetPos() { return this->m_Position; };
		inline sf::Vector2f& GetVel() { return this->m_Velocity; };
		inline int GetHP() { return this->m_Life; };

		void Update(EnemyList& _enemyList, TileMap& _map, Window& _window);
		void Display(Window& _window);

		bool CheckDamage();

		void Ready();
		void Die();
		void Respawn();
};