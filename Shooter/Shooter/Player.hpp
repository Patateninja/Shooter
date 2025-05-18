#pragma once
#include "Shotgun.hpp"
#include "Enemy.hpp"

class Player
{
	private :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		Shotgun m_Shotgun;
		float m_InputTimer;
		int m_Life;
		bool m_CanMove;
		bool m_CanReload;
	public :
		Player();
		~Player();

		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); }
		inline sf::Vector2f& GetPos() { return this->m_Position; }
		inline sf::Vector2f& GetVel() { return this->m_Velocity; }
		inline int GetHP() { return this->m_Life; }
		inline void SetHP(int _life) { this->m_Life = _life; }
		inline void AddHP(int _life) { this->m_Life += _life; }

		void Update(EnemyList& _enemyList, TileMap& _map, Window& _window);
		void Display(Window& _window);

		bool CheckDamage();

		void Ready();
		void Die();
		void Respawn();
};