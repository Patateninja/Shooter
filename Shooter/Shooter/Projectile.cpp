#include "Projectile.hpp"
#include <iostream>

//////////////////////////////////////////////////

Projectile::Projectile()
{
	this->m_Circle = sf::CircleShape(2.5f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Type = CLASSIC;
	switch (this->m_Type)
	{
		case FLAMMING :
			this->m_Circle.setFillColor(sf::Color::Red);
			break;
		case PIERCING :
			this->m_Circle.setFillColor(sf::Color::Yellow);
			break;
		default :
			this->m_Circle.setFillColor(sf::Color::White);
			break;
	}
	this->m_Damage = 0;
	this->m_Range = 0;
	this->m_Distance = 0.f;
	this->m_ToDestroy = false;
}
Projectile::Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range)
{
	this->m_Circle = sf::CircleShape(2.5f);
	this->m_Position = _pos;
	this->m_Velocity = _vel;
	this->m_Type = _type;
	switch (this->m_Type)
	{
		case FLAMMING:
			this->m_Circle.setFillColor(sf::Color::Red);
			break;
		case PIERCING:
			this->m_Circle.setFillColor(sf::Color::Yellow);
			break;
		default:
			this->m_Circle.setFillColor(sf::Color::White);
			break;
	}
	this->m_Damage = _dmg;
	this->m_Range = _range;
	this->m_Distance = 0.f;
	this->m_ToDestroy = false;
}
Projectile::~Projectile()
{

}

bool Projectile::Update(float _deltatime)
{
	if (!this->m_ToDestroy)
	{
		sf::Vector2f mvt = this->m_Velocity * _deltatime;
		this->m_Position += mvt;
		this->m_Distance += Tools::Magnitude(mvt);

		this->m_Circle.setPosition(this->m_Position);

		if (this->m_Distance > this->m_Range)
		{
			return true;
		}
		return false;
	}
	else
	{
		return true;
	}
}

void Projectile::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

//////////////////////////////////////////////////

ProjectileList::ProjectileList()
{
	this->m_List.clear();
}
ProjectileList::~ProjectileList()
{
	this->m_List.clear();
}

void ProjectileList::Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range)
{
	this->m_List.push_back(std::make_unique<Projectile>(_pos, _vel, _type, _dmg, _range));
}
void ProjectileList::Add(Projectile& _proj)
{
	this->m_List.push_back(std::make_unique<Projectile>(_proj));
}

void ProjectileList::Update(float _deltatime)
{
	for (auto proj = this->m_List.begin(); proj != this->m_List.end(); ++proj)
	{
		if ((*proj)->GetToDestroy() || (*proj)->Update(_deltatime))
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
	for (std::unique_ptr<Projectile>& proj : this->m_List)
	{
		proj->Display(_window);
	}
}

void ProjectileList::Clear()
{
	for (std::unique_ptr<Projectile>& projectile : this->m_List)
	{
		projectile.release();
	}

	this->m_List.clear();
}

//////////////////////////////////////////////////

namespace ProjList
{
	ProjectileList list;

	std::list<std::unique_ptr<Projectile>>& GetList()
	{
		return ProjList::list.GetList();
	}

	void Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range)
	{
		ProjList::list.Add(_pos, _vel, _type, _dmg, _range);
	}
	void Add(Projectile& _proj)
	{
		ProjList::list.Add(_proj);
	}

	void Update(float _deltatime)
	{
		ProjList::list.Update(_deltatime);
	}
	void Display(Window& _window)
	{
		ProjList::list.Display(_window);
	}

	void Clear()
	{
		ProjList::list.Clear();
	}

	int Size()
	{
		return ProjList::list.Size();
	}
}

//////////////////////////////////////////////////
