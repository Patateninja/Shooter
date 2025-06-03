#pragma once
#include "Shotgun.hpp"
#include "Enemy.hpp"
#include "Equipement.hpp"
#include "Camera.hpp"

typedef enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

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
		float m_Angle = 0.f;
		float m_InputTimer = 0.f;
		int m_Life = 30;
		int m_Vest = 0;
		int m_MaxAmmo = 5;
		int m_BuckShot = 5;
		int m_DragonBreath = 5;
		int m_Slug = 5;
		bool m_CanMove = false;
		bool m_CanReload = true;
		bool m_Caffeinated = false;
		bool m_Got50BMG = false;

	public :
		Player();
		~Player() = default;

		void Init(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock, Armor& _armor, AmmoStash& _ammoStash);

		inline const sf::Vector2f& GetPos() const { return this->m_Position; }
		inline const sf::Vector2f& GetVel() const { return this->m_Velocity; }
		inline const int GetHP() const { return this->m_Life; }
		inline const int GetVest() const { return this->m_Vest; }
		inline const bool GetMoving() const { return this->m_CanMove; }

		inline void SetTimer(float _timer) { this->m_InputTimer = _timer; }

		void Update(EnemyList& _enemyList, TileMap& _map, Camera& _cam, Window& _window);
		void Display(Window& _window);

		void ModifyShotgun(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock);
		void Equip(Armor& _armor, AmmoStash& _ammoStash);

		bool CheckWallCollision(TileMap& _map, Direction _direction);

		bool CheckDamage();

		void Ready();
		void Die();
		void Respawn();

		void Refill();
		void Heal();
		void AddVest();
		void Coffee(bool _coffee);
		void BMG50(bool _bmg);
};