#pragma once
#include "Shotgun.hpp"
#include "Enemy.hpp"
#include "Equipment.hpp"
#include "Camera.hpp"

typedef enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
} Direction;

class Player
{
	private :
		Shotgun m_Shotgun;
		sf::CircleShape m_Circle;
		Armor m_Armor;
		AmmoStash m_AmmoStash;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		float m_Angle = 0.f;
		float m_InputTimer = 0.f;
		int m_Life = 3;
		int m_Vest = 1;
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

		inline const sf::Vector2f& GetPos()    const { return this->m_Position; }
		inline const sf::Vector2f& GetVel()    const { return this->m_Velocity; }
		inline const int           GetHP()     const { return this->m_Life; }
		inline const int           GetVest()   const { return this->m_Vest; }
		inline const bool          GetMoving() const { return this->m_CanMove; }

		inline int&			  GetBuckshot()     { return this->m_BuckShot; }
		inline int&			  GetDragonBreath() { return this->m_DragonBreath; }
		inline int&			  GetSlug()         { return this->m_Slug; }
		inline Shotgun&		  GetShotgun()      { return this->m_Shotgun; }
		inline const bool     GetBmgEnabled()  const { return this->m_Got50BMG; }
		inline const bool     GetCoffeeEnabled()  const { return this->m_Caffeinated; }
		

		inline void SetTimer(float _timer) { this->m_InputTimer = _timer; }

		void Update(EnemyList& _enemyList, TileMap& _map, Camera& _cam, Window& _window);
		void Display(Window& _window);

		void ModifyShotgun(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock);
		void Equip(Armor& _armor, AmmoStash& _ammoStash);

		bool CheckWallCollision(TileMap& _map, Direction _direction);

		bool CheckDamage();

		void Ready();
		void Die(EnemyList& _enemyList, TileMap& _map, Camera& _cam, Window& _window);
		void Respawn();

		void Unload();
		void Refill();
		void Heal();
		void AddVest();
		void Coffee(bool _coffee);
		void BMG50(bool _bmg);
};