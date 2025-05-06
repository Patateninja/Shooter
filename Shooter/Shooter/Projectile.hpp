#pragma once
#include "tools.hpp"
#include "Window.hpp"
#include <list>

typedef enum ProjectileType
{
	CLASSIC,
	FLAMMING,
	PIERCING,
} ProjectileType;

class Projectile
{
	private :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		ProjectileType m_Type;
		int m_Damage;
		int m_Range;
		float m_Distance;
		bool m_ToDestroy;
	public :
		Projectile();
		Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
		~Projectile();

		inline sf::Vector2f GetPos() { return this->m_Position; };
		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline int GetDamage() { return this->m_Damage; };
		inline bool GetToDestroy() { return this->m_ToDestroy; };
		
		inline void SetToDestroy(bool _set) { this->m_ToDestroy = _set; };

		bool Update(float _deltatime);
		void Display(Window& _window);
};

class ProjectileList
{
	private :
		std::list<std::unique_ptr<Projectile>> m_list;
	public :
		ProjectileList();
		~ProjectileList();

		inline std::list<std::unique_ptr<Projectile>>& GetList() { return this->m_list ; };

		void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
		void Add(Projectile& _proj);

		void Update(float _deltatime);
		void Display(Window& _window);

		int Size() { return int(this->m_list.size()); };
};

namespace ProjList
{
	std::list<std::unique_ptr<Projectile>>& GetList();

	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range);
	void Add(Projectile& _proj);

	void Update(float _deltatime);
	void Display(Window& _window);

	int Size();
}