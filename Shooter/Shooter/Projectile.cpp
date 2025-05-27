#include "Projectile.hpp"

//////////////////////////////////////////////////

Projectile::Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team)
{
	this->m_Circle = sf::CircleShape(5.f);
	this->m_Circle.setOrigin(sf::Vector2f(5.f, 5.f));
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Position = _pos;
	this->m_Velocity = _vel;
	this->m_Type = _type;
	this->m_Team = _team;
	this->m_Damage = _dmg;
	this->m_Range = _range;
}

bool Projectile::Update(float _deltatime, TileMap& _map)
{
	if (!this->m_ToDestroy)
	{
		this->m_Position += this->m_Velocity * _deltatime;
		this->m_Distance += Tools::Magnitude(this->m_Velocity * _deltatime);

		this->m_Circle.setPosition(this->m_Position);

		if (this->m_Distance > this->m_Range || !_map.GetTile(this->m_Position.x, this->m_Position.y).GetBulletThrough() || !_map.GetTile(this->m_Position.x + 1, this->m_Position.y + 1).GetBulletThrough())
		{
			return true;
		}
		return false;
	}
	return true;
}

void Projectile::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

//////////////////////////////////////////////////

ProjectileList::~ProjectileList()
{
	this->Clear();
}

void ProjectileList::Update(TileMap& _map)
{
	for (std::list<std::shared_ptr<Projectile>>::iterator proj = this->m_List.begin(); proj != this->m_List.end(); ++proj)
	{
		if (proj->get()->GetToDestroy() || proj->get()->Update(Time::GetDeltaTime(), _map))
		{
			proj = this->m_List.erase(proj);
			if (proj == this->m_List.end())
			{
				break;
			}
		}
	}
}

void ProjectileList::Display(Window& _window)
{
	for (std::shared_ptr<Projectile>& proj : this->m_List)
	{
		proj->Display(_window);
	}
}

void ProjectileList::Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team)
{
	this->m_List.push_back(std::make_shared<Projectile>(_pos, _vel, _type, _dmg, _range, _team));
}
void ProjectileList::Clear()
{
	for (std::shared_ptr<Projectile>& projectile : this->m_List)
	{
		projectile.reset();
	}

	this->m_List.clear();
}

//////////////////////////////////////////////////

namespace ProjList
{
	ProjectileList list;

	const std::list<std::shared_ptr<Projectile>>& GetList()
	{
		return ProjList::list.GetList();
	}
	const int GetSize()
	{
		return ProjList::list.GetSize();
	}

	void Update(TileMap& _map)
	{
		ProjList::list.Update(_map);
	}
	void Display(Window& _window)
	{
		ProjList::list.Display(_window);
	}

	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range, Team _team)
	{
		ProjList::list.Add(_pos, _vel, _type, _dmg, _range, _team);
	}
	void Clear()
	{
		ProjList::list.Clear();
	}
}

//////////////////////////////////////////////////
