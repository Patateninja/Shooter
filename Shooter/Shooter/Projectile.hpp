#pragma once
#include "tools.hpp"
#include "Window.hpp"
#include <list>

typedef enum ProjectileType
{
	CLASSIC,
	FLAMMING,
	PIERCING,
};

class Projectile
{
	private :
		sf::CircleShape m_circle;
		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		ProjectileType m_Type;
		int m_damage;
		int m_range;
		float m_distance;
	public :
		Projectile();
		Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
		~Projectile();

		inline sf::Vector2f GetPos() { return this->m_position; };

		bool Update(float _deltatime);
		void Display(Window& _win);
};

class ProjectileList
{
	private :
		std::list<std::unique_ptr<Projectile>> m_list;
	public :
		ProjectileList();
		~ProjectileList();

		void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
		void Add(Projectile& _proj);

		void Update(float _deltatime);
		void Display(Window& _win);

		int Size() { return this->m_list.size(); };
};

namespace ProjList
{
	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
	void Add(Projectile& _proj);

	void Update(float _deltatime);
	void Display(Window& _window);

	int Size();
}