#pragma once
#include "Tile.hpp"
#include "Window.hpp"

typedef enum ProjectileType
{
	CLASSIC,
	FLAMMING,
	PIERCING,
} ProjectileType;

typedef enum Team
{
	PLAYER,
	ENEMY,
} Team;

class Projectile
{
	private :
		sf::CircleShape m_Circle;
		sf::Vector2f m_Position;
		sf::Vector2f m_Velocity;
		ProjectileType m_Type;
		Team m_Team;
		int m_Damage;
		int m_Range;
		float m_Distance;
		bool m_ToDestroy;
	public :
		Projectile();
		Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
		~Projectile();

		inline sf::Vector2f GetPos() { return this->m_Position; };
		inline sf::FloatRect GetHitbox() { return this->m_Circle.getGlobalBounds(); };
		inline int GetDamage() { return this->m_Damage; };
		inline bool GetToDestroy() { return this->m_ToDestroy; };
		inline ProjectileType GetType() { return this->m_Type; };
		inline Team GetTeam() { return this->m_Team; };

		inline void SetToDestroy(bool _set) { this->m_ToDestroy = _set; };

		bool Update(float _deltatime, TileMap& _map);
		void Display(Window& _window);
};

class ProjectileList
{
	private :
		std::list<std::shared_ptr<Projectile>> m_List;
	public :
		ProjectileList();
		~ProjectileList();

		inline std::list<std::shared_ptr<Projectile>>& GetList() { return this->m_List ; };

		void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
		void Add(Projectile& _proj);

		void Update(TileMap& _map);
		void Display(Window& _window);

		void Clear();

		int Size() { return int(this->m_List.size()); };
};

namespace ProjList
{
	std::list<std::shared_ptr<Projectile>>& GetList();

	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
	void Add(Projectile& _proj);

	void Update(TileMap& _map);
	void Display(Window& _window);

	void Clear();

	int Size();
}