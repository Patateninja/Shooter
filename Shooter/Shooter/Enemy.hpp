#pragma once
#include "Projectile.hpp"
#include "Astar.hpp"
#include "Shield.hpp"
#include "Xp.hpp"
#include <thread>
#include <future>

class Enemy
{
	protected :
		std::vector<std::weak_ptr<Projectile>> m_IgnoreProj;
		sf::CircleShape m_Circle;
		std::list<Tile> m_Path;
		std::thread m_Thread;
		sf::Vector2f m_StartingPosition;
		sf::Vector2f m_Position;
		sf::Vector2f m_ProjectileOrigin;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		int m_MaxHp = 0.f;
		int m_Hp = 0.f;
		int m_BurningDamage = 0.f;
		float m_AttackRange = 0.f;
		float m_Speed = 0.f;
		float m_BurnCooldown = 0.f;
		float m_PathUdpateCooldown = 0.f;
		bool m_Burning = false;
		bool m_Active = false;
	public :
		Enemy() = default;
		Enemy(const sf::Vector2f& _stratingPos);
		~Enemy();

		inline float GetRange() { return this->m_AttackRange; };
		inline sf::Vector2f GetPos() { return this->m_Position; };
		inline sf::Vector2f GetProjOrigin() { return this->m_ProjectileOrigin; };
		inline int GetHP() { return this->m_Hp; };
		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline bool GetActive() { return this->m_Active; };
		inline void SetActive(bool _input) { this->m_Active = _input; };

		void Respawn();

		virtual void Update(sf::Vector2f& _playerPos, TileMap& _map);
		virtual void Display(Window& _window);

		bool PlayerInSight(sf::Vector2f _playerPos, TileMap& _map);
		void UpdatePath(sf::Vector2f& _playerPos, TileMap& _map);
		void Move(sf::Vector2f& _playerPos, TileMap& _map);
		void CheckDamage();
		void TakeDamage(std::shared_ptr<Projectile>& _projectile);
		void TakeDamage(int _damage);
		void Die();
};

class Baseliner : public Enemy
{
	public :
		Baseliner(const sf::Vector2f& _stratingPos);
		~Baseliner();
};

class Tank : public Enemy
{
	public:
		Tank(const sf::Vector2f& _stratingPos);
		~Tank();
};

class Ranged : public Enemy
{
	private :
		float m_ShootTimer;
	public:
		Ranged(const sf::Vector2f& _stratingPos);
		~Ranged();

		void Update(sf::Vector2f& _playerPos, TileMap& _map) override;

		bool CanShoot(sf::Vector2f _playerPos);
		void Shoot(sf::Vector2f& _playerPos);
};

class Swarmer : public Enemy
{
	public:
		Swarmer(const sf::Vector2f& _stratingPos);
		~Swarmer();
};

class Shielded : public Enemy
{
	private :
		std::unique_ptr<Shield> m_Shield;
	public:
		Shielded(const sf::Vector2f& _stratingPos);
		~Shielded();

		void Update(sf::Vector2f& _playerPos, TileMap& _map) override;
		void Display(Window& _window) override;
};

class RangedShielded : public Enemy
{
	private:
		float m_ShootTimer;
		std::unique_ptr<Shield> m_Shield;
	public:
		RangedShielded(const sf::Vector2f& _stratingPos);
		~RangedShielded();

		void Update(sf::Vector2f& _playerPos, TileMap& _map) override;
		void Display(Window& _window) override;

		bool CanShoot(sf::Vector2f _playerPos);
		void Shoot(sf::Vector2f& _playerPos);
};

class EnemyList
{
	private :
		std::list<std::shared_ptr<Enemy>> m_List;
	public :
		EnemyList();
		~EnemyList();

		inline std::list<std::shared_ptr<Enemy>>& GetList() { return this->m_List; };

		template <typename T>
		void Add(const sf::Vector2f& _startingPos)
		{
			this->m_List.push_back(std::make_unique<T>(_startingPos));
		}
		template <typename T>
		void Add(Enemy& _enemy)
		{
			this->m_List.push_back(std::make_unique<Enemy>(_enemy));
		}
		void Clear();

		bool AllDead();

		void Update(sf::Vector2f& _playerPos, TileMap& _map);
		void Display(Window& _window);

		void Activate();
		void Respawn();

		inline int Size() { return int(this->m_List.size()); };
		inline int Alive() { int i = 0; for (std::shared_ptr<Enemy>& enemy : this->m_List) { if (enemy->GetHP() > 0) { ++i; } } return i; }
};