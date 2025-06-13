#pragma once
#include "Projectile.hpp"
#include "Astar.hpp"
#include "Shield.hpp"
#include "Xp.hpp"
#include <thread>
#include <mutex>

typedef enum IdleBehavior
{
	PATROL,
	WANDER,
	GUARD,
} IdleBehavior;

class Enemy
{
	protected :
		sf::CircleShape m_Circle;
		std::vector<std::weak_ptr<Projectile>> m_IgnoreProj;
		std::vector<Tile> m_PatrolTargets;
		std::list<Tile> m_Path;
		std::mutex m_Mutex;
		std::thread m_MovingThread;
		std::thread m_PathfidingThread;
		Tile m_IdleTileTarget;
		sf::Vector2f m_StartingPosition;
		sf::Vector2f m_Position;
		sf::Vector2f m_ProjectileOrigin;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		IdleBehavior m_IdleBehavior = WANDER;
		int m_MaxHp = 0;
		int m_Hp = 0;
		int m_BurningDamage = 0;
		float m_AttackRange = 0.f;
		float m_Speed = 0.f;
		float m_BurnCooldown = 0.f;
		float m_PathUdpateCooldown = 0.f;
		float m_SeePlayerUdpateCooldown = 0.f;
		float m_LosePlayerCooldown = 0.f;
		float m_Angle = 0.f;
		float m_DefaultAngle = this->m_Angle = Tools::Random(3, -1) * 90.f;;
		bool m_Burning = false;
		bool m_Active = false;
		bool m_SeePlayer = false;
		bool m_CanAimPlayer = false;
		bool m_Idle = true;
		bool m_Alive = true;

	public :
		Enemy() = default;
		Enemy(const sf::Vector2f& _stratingPos, TileMap& _map);
		~Enemy();

		inline const float GetRange() const { return this->m_AttackRange; };
		inline const sf::Vector2f GetPos() const { return this->m_Position; };
		inline const sf::Vector2f GetProjOrigin()const { return this->m_ProjectileOrigin; };
		inline const int GetHP() const { return this->m_Hp; };
		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline const bool GetActive() const { return this->m_Active; };
		inline void SetActive(bool _input) { this->m_Active = _input; };

		void Respawn(TileMap& _map);

		void MakePatrolPath(TileMap& _map);

		virtual void Update(const sf::Vector2f& _playerPos, TileMap& _map);
		virtual void Display(Window& _window);

		void HearSound(sf::Vector2f& _soundPos, int _soundIntensity);
		bool SeePlayer(const sf::Vector2f& _playerPos, TileMap& _map) const;
		bool PlayerAimable(const sf::Vector2f& _playerPos, TileMap& _map) const;
		
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
		Baseliner(const sf::Vector2f& _stratingPos, TileMap& _map);
		~Baseliner();
};

class Tank : public Enemy
{
	public:
		Tank(const sf::Vector2f& _stratingPos, TileMap& _map);
		~Tank();
};

class Ranged : public Enemy
{
	private :
		float m_ShootTimer;

	public:
		Ranged(const sf::Vector2f& _stratingPos, TileMap& _map);
		~Ranged();

		void Update(const sf::Vector2f& _playerPos, TileMap& _map) override;

		void Shoot(const sf::Vector2f& _playerPos);
};

class Speedster : public Enemy
{
	public:
		Speedster(const sf::Vector2f& _stratingPos, TileMap& _map);
		~Speedster();
};

class Shielded : public Enemy
{
	private :
		std::unique_ptr<Shield> m_Shield;

	public:
		Shielded(const sf::Vector2f& _stratingPos, TileMap& _map);
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
		RangedShielded(const sf::Vector2f& _stratingPos, TileMap& _map);
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
		void Add(const sf::Vector2f& _startingPos, TileMap& _map)
		{
			this->m_List.push_back(std::make_unique<T>(_startingPos, _map));
		}
		template <typename T>
		void Add(Enemy& _enemy, TileMap& _map)
		{
			this->m_List.push_back(std::make_unique<Enemy>(_enemy, _map));
		}
		void Clear();

		bool AllDead();

		void Update(const sf::Vector2f& _playerPos, TileMap& _map);
		void Display(Window& _window);

		void AllHearSound(sf::Vector2f& _soundPos, int _soundIntensity);

		void Activate();
		void Respawn(TileMap& _map);

		inline int Size() { return int(this->m_List.size()); };
		inline int Alive() { int i = 0; for (std::shared_ptr<Enemy>& enemy : this->m_List) { if (enemy->GetHP() > 0) { ++i; } } return i; }
};