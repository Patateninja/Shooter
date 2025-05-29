#pragma once
#include "Tile.hpp"

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
		ProjectileType m_Type = CLASSIC;
		Team m_Team = PLAYER;
		float m_Distance = 0.f;
		int m_Damage = 0;
		int m_Range = 0;
		bool m_ToDestroy = false;

	public :
		Projectile() = default;
		Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
		~Projectile() = default;

		inline const sf::Vector2f GetPos() const { return this->m_Position; }
		inline const sf::FloatRect GetHitbox() const { return this->m_Circle.getGlobalBounds(); }
		inline const ProjectileType GetType() const { return this->m_Type; }
		inline const Team GetTeam() const { return this->m_Team; }
		inline const int GetDamage() const { return this->m_Damage; }
		inline const bool GetToDestroy() const { return this->m_ToDestroy; }

		inline void SetToDestroy(bool _set) { this->m_ToDestroy = _set; }

		bool Update(float _deltatime, TileMap& _map);
		void Display(Window& _window);
};

class ProjectileList
{
	private :
		std::list<std::shared_ptr<Projectile>> m_List;

	public :
		ProjectileList() = default;
		~ProjectileList();

		inline std::list<std::shared_ptr<Projectile>>& GetList() { return this->m_List ; }
		inline const int GetSize() { return int(this->m_List.size()); }

		void Update(TileMap& _map);
		void Display(Window& _window);

		void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
		void Clear();
};

namespace ProjList
{
	std::list<std::shared_ptr<Projectile>>& GetList();
	const int GetSize();

	void Update(TileMap& _map);
	void Display(Window& _window);

	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team);
	void Clear();
}