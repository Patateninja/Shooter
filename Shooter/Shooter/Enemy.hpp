#pragma once
#include "Projectile.hpp"
#include "Astar.hpp"

class Enemy
{
	protected :
		std::vector<std::weak_ptr<Projectile>> m_IgnoreProj;
		sf::CircleShape m_Circle;
		std::list<Tile> m_Path;
		sf::Vector2f m_StartingPosition;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		int m_MaxHp;
		int m_Hp;
		int m_BurningDamage;
		float m_Speed;
		float m_BurnCoolDown;
		bool m_Burning;
		bool m_Active;
	public :
		Enemy();
		Enemy(const sf::Vector2f& _stratingPos);
		~Enemy();

		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline bool GetActive() { return this->m_Active; };
		inline void SetActive(bool _input) { this->m_Active = _input; };

		void Respawn();

		void Update(sf::Vector2f& _playerPos, TileMap& _map);
		void Display(Window& _window);

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
	public:
		Ranged(const sf::Vector2f& _stratingPos);
		~Ranged();
};

class Swarmer : public Enemy
{
	public:
		Swarmer(const sf::Vector2f& _stratingPos);
		~Swarmer();
};

class Shielded : public Enemy
{
	public:
		Shielded(const sf::Vector2f& _stratingPos);
		~Shielded();
};

class RangedShielded : public Enemy
{
	public:
		RangedShielded(const sf::Vector2f& _stratingPos);
		~RangedShielded();
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

		void Update(sf::Vector2f& _playerPos, TileMap& _map);
		void Display(Window& _window);

		void Activate();
		void Respawn();

		inline int Size() { return int(this->m_List.size()); };
};