#include "Projectile.hpp"
#include <iostream>

//////////////////////////////////////////////////

Projectile::Projectile()
{
	this->m_circle = sf::CircleShape(2.5f);
	this->m_position = sf::Vector2f(0.f, 0.f);
	this->m_velocity = sf::Vector2f(0.f, 0.f);
	this->m_Type = CLASSIC;
	switch (this->m_Type)
	{
		case FLAMMING :
			this->m_circle.setFillColor(sf::Color::Red);
			break;
		case PIERCING :
			this->m_circle.setFillColor(sf::Color::Yellow);
			break;
		default :
			this->m_circle.setFillColor(sf::Color::White);
			break;
	}
	this->m_damage = 0;
	this->m_range = 0;
	this->m_distance = 0.f;
}
Projectile::Projectile(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range)
{
	this->m_circle = sf::CircleShape(2.5f);
	this->m_position = _pos;
	this->m_velocity = _vel;
	this->m_Type = _type;
	switch (this->m_Type)
	{
		case FLAMMING:
			this->m_circle.setFillColor(sf::Color::Red);
			break;
		case PIERCING:
			this->m_circle.setFillColor(sf::Color::Yellow);
			break;
		default:
			this->m_circle.setFillColor(sf::Color::White);
			break;
	}
	this->m_damage = _dmg;
	this->m_range = _range;
	this->m_distance = 0.f;
}
Projectile::~Projectile()
{

}

bool Projectile::Update(float _deltatime)
{
	sf::Vector2f mvt = this->m_velocity * _deltatime;
	this->m_position += mvt;
	this->m_distance += Tools::Magnitude(mvt);

	this->m_circle.setPosition(this->m_position);

	if (this->m_distance > this->m_range)
	{
		return true;
	}
	return false;
}

void Projectile::Display(Window& _win)
{
	_win.Draw(this->m_circle);
}

//////////////////////////////////////////////////

ProjectileList::ProjectileList()
{
	this->m_list.clear();
}
ProjectileList::~ProjectileList()
{

}

void ProjectileList::Add(sf::Vector2f _pos, sf::Vector2f _vel, ProjectileType _type, int _dmg, int _range)
{
	this->m_list.push_back(std::make_unique<Projectile>(_pos, _vel, _type, _dmg, _range));
}
void ProjectileList::Add(Projectile& _proj)
{
	this->m_list.push_back(std::make_unique<Projectile>(_proj));
}

void ProjectileList::Update(float _deltatime)
{
	for (auto proj = this->m_list.begin(); proj != this->m_list.end(); ++proj)
	{
		if ((*proj)->Update(_deltatime) || (*proj)->GetPos().x > 1920.f || (*proj)->GetPos().y > 1080.f)
		{
			proj = this->m_list.erase(proj);
			if (proj == this->m_list.end())
			{
				break;
			}
		}
	}
}

void ProjectileList::Display(Window& _win)
{
	for (std::unique_ptr<Projectile>& proj : this->m_list)
	{
		proj->Display(_win);
	}
}

//////////////////////////////////////////////////