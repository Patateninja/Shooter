#pragma once
#include "Window.hpp"
#include "Projectile.hpp"
#include "ResourceManager.hpp"

class Enemy
{
	protected :
		sf::CircleShape m_Circle;
		sf::Vector2f m_StartingPosition;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		sf::Vector2f m_Target;
		int m_MaxHp;
		int m_Hp;
		int m_BurningDamage;
		float m_BurnCoolDown;
		bool m_Burning;
		bool m_Active;
	public :
		Enemy();
		Enemy(const sf::Vector2f& _stratingPos);
		~Enemy();

		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };

		void SetActive(bool _input) { this->m_Active = _input; };

		void Respawn();

		void Update(float _deltatime, sf::Vector2f& _playerPos);
		void Display(Window& _window);

		void Move(float _deltatime);
		void CheckDamage();
		void TakeDamage(Projectile& _projectile);
		void TakeDamage(int _damage);
		void Die();
};

class EnemyList
{
	private :
		std::list<std::shared_ptr<Enemy>> m_List;
	public :
		EnemyList();
		~EnemyList();

		inline std::list<std::shared_ptr<Enemy>>& GetList() { return this->m_List; };

		void Add(const sf::Vector2f& _startingPos);
		void Add(Enemy& _enemy);
		void Clear();

		void Update(float _deltatime, sf::Vector2f& _playerPos);
		void Display(Window& _window);

		void Activate();
		void Respawn();

		inline int Size() { return int(this->m_List.size()); };
};