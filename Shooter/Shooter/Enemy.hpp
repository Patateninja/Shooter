#pragma once
#include "Projectile.hpp"
#include "Astar.hpp"
#include "Shield.hpp"
#include "Xp.hpp"
#include <thread>
#include <mutex>

class Enemy
{
	protected :
		sf::CircleShape m_Circle;
		std::vector<std::weak_ptr<Projectile>> m_IgnoreProj;
		std::list<Tile> m_Path;
		std::mutex m_Mutex;
		std::thread m_MovingThread;
		std::thread m_PathfidingThread;

		sf::Vector2f m_StartingPosition;
		sf::Vector2f m_Position;
		sf::Vector2f m_ProjectileOrigin;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		int m_MaxHp = 0;
		int m_Hp = 0;
		int m_BurningDamage = 0;
		float m_AttackRange = 0.f;
		float m_Speed = 0.f;
		float m_BurnCooldown = 0.f;
		float m_PathUdpateCooldown = 0.f;
		float m_SeePlayerUdpateCooldown = 0.f;
		float m_ActionRange = Tile::GetSize() * 25.f;
		bool m_Burning = false;
		bool m_Active = false;
		bool m_SeePlayer = false;

	public :
		Enemy() = default;
		Enemy(const sf::Vector2f& _stratingPos);
		~Enemy();

		inline const float GetRange() const { return this->m_AttackRange; };
		inline const sf::Vector2f GetPos() const { return this->m_Position; };
		inline const sf::Vector2f GetProjOrigin()const { return this->m_ProjectileOrigin; };
		inline const int GetHP() const { return this->m_Hp; };
		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline const bool GetActive() const { return this->m_Active; };
		inline void SetActive(bool _input) { this->m_Active = _input; };

		void Respawn();
		void Threadlauncher() { return; }

		virtual void Update(const sf::Vector2f& _playerPos, TileMap& _map);
		virtual void Display(Window& _window);

		bool PlayerInSight(const sf::Vector2f& _playerPos, TileMap& _map);
		void UpdatePath(const sf::Vector2f& _playerPos, TileMap& _map);
		void Move(const sf::Vector2f& _playerPos, TileMap& _map);
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

		void Update(const sf::Vector2f& _playerPos, TileMap& _map) override;

		void Shoot(const sf::Vector2f& _playerPos);
};

class Speedster : public Enemy
{
	public:
		Speedster(const sf::Vector2f& _stratingPos);
		~Speedster();
};

class Shielded : public Enemy
{
	private :
		std::unique_ptr<Shield> m_Shield;

	public:
		Shielded(const sf::Vector2f& _stratingPos);
		~Shielded();

		void Update(const sf::Vector2f& _playerPos, TileMap& _map) override;
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

		void Update(const sf::Vector2f& _playerPos, TileMap& _map) override;
		void Display(Window& _window) override;

		void Shoot(const sf::Vector2f& _playerPos);
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

		void Update(const sf::Vector2f& _playerPos, TileMap& _map);
		void Display(Window& _window);

		void Activate();
		void Respawn();

		inline int Size() { return int(this->m_List.size()); };
		inline int Alive() { int i = 0; for (std::shared_ptr<Enemy>& enemy : this->m_List) { if (enemy->GetHP() > 0) { ++i; } } return i; }
};