#include "Enemy.hpp"

////////////////////////////////////////////////////////
#pragma region Enemy

Enemy::Enemy(const sf::Vector2f& _startingPos)
{
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
}
Enemy::~Enemy()
{
	this->m_IgnoreProj.clear();
}

void Enemy::Respawn()
{
	this->m_Position = this->m_StartingPosition;
	this->m_Circle.setPosition(this->m_StartingPosition);
	this->m_Hp = this->m_MaxHp;
	this->m_Active = false;
	this->m_Burning = false;
	this->m_BurnCooldown = 0.f;
	this->m_BurningDamage = 0;
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_IgnoreProj.clear();
	this->m_Path.clear();
}

void Enemy::Update(sf::Vector2f& _playerPos, TileMap& _map)
{
	if (this->m_Active)
	{
		if (this->m_PathUdpateCooldown <= 0.f || this->m_Path.empty())
		{
			this->UpdatePath(_playerPos, _map);
			this->m_PathUdpateCooldown = 0.75f;
		}
		else
		{
			this->m_PathUdpateCooldown -= Time::GetDeltaTime();
		}
		if (Tools::Distance(this->m_Position, _playerPos) > this->m_AttackRange)
		{
			this->Move(_playerPos, _map);
		}
		this->CheckDamage();

		if (this->m_Burning)
		{
			this->m_BurnCooldown -= Time::GetDeltaTime();
		}
		if (this->m_BurnCooldown < 0.f)
		{
			this->TakeDamage(this->m_BurningDamage);
			this->m_BurnCooldown = 3.f;
		}
	}
}
void Enemy::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

void Enemy::UpdatePath(sf::Vector2f& _playerPos, TileMap& _map)
{
	this->m_Path = Astar::Pathfinding(_map.GetTile(this->m_Position.x,this->m_Position.y), _map.GetTile(_playerPos.x, _playerPos.y), _map);
}
void Enemy::Move(sf::Vector2f& _playerPos, TileMap& _map)
{
	this->m_Target = this->m_Path.front().GetCood();
	this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed;

	this->m_Position += this->m_Velocity * Time::GetDeltaTime();
	this->m_Circle.setPosition(this->m_Position);

	if (_map.GetTile(this->m_Position.x,this->m_Position.y) == this->m_Path.front())
	{
		this->m_Path.erase(this->m_Path.begin());
	}
}
void Enemy::CheckDamage()
{
	for (std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == PLAYER && [&](auto _list, std::shared_ptr<Projectile>& _proj) -> bool { for (auto pr : _list) { if (proj == pr.lock()) { return false; } } return true; } (this->m_IgnoreProj, proj))
		{
			TakeDamage(proj);
		}
	}
}
void Enemy::TakeDamage(std::shared_ptr<Projectile>& _projectile)
{
	this->m_Hp -= _projectile->GetDamage();

	if (_projectile->GetType() != PIERCING)
	{
			_projectile->SetToDestroy(true);
	}
	else
	{
		this->m_IgnoreProj.push_back(_projectile);
	}

	if (_projectile->GetType() == FLAMMING)
	{
		this->m_Burning = true;
		this->m_BurnCooldown = 3.f;
		this->m_BurningDamage += _projectile->GetDamage();
		this->m_Circle.setFillColor(sf::Color(255, 155, 0, 255));
	}

	if (this->m_Hp <= 0)
	{
		this->Die();
	}
}
void Enemy::TakeDamage(int _damage)
{
	this->m_Hp -= _damage;

	if (this->m_Hp <= 0)
	{
		this->Die();
	}
}
void Enemy::Die()
{
	this->m_Active = false;
	this->m_Circle.setFillColor(sf::Color(125, 125, 125, 255));
	this->m_IgnoreProj.clear();
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Enemy_Types
#pragma region Baseliner

Baseliner::Baseliner(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 35;
	this->m_Hp = 35;
	this->m_Speed = 250.f;
}
Baseliner::~Baseliner()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Tank

Tank::Tank(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(30.f);
	this->m_Circle.setOrigin(30.f, 30.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 75;
	this->m_Hp = 75;
	this->m_Speed = 200.f;
}
Tank::~Tank()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Ranged

Ranged::Ranged(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_AttackRange = Tile::GetSize() * 7.f;
	this->m_MaxHp = 25;
	this->m_Hp = 25;
	this->m_Speed = 250.f;
	this->m_ShootTimer = 3.f;
}
Ranged::~Ranged()
{

}

void Ranged::Update(sf::Vector2f& _playerPos, TileMap& _map)
{
	Enemy::Update(_playerPos, _map);
	if (this->m_Active && this->CanShoot(_playerPos))
	{
		this->Shoot(_playerPos);
	}
}

bool Ranged::Aimable(sf::Vector2f _playerPos)
{	
	return true;
}
bool Ranged::CanShoot(sf::Vector2f _playerPos)
{
	return (Tools::Distance(this->m_Position, _playerPos) < Tile::GetSize() * 7 && this->Aimable(_playerPos));
}
void Ranged::Shoot(sf::Vector2f& _playerPos)
{
	if (this->m_ShootTimer <= 0.f)
	{
		ProjList::Add(this->m_Position, Tools::AngleToVector(1000, Tools::VectorToAngle(_playerPos- this->m_Position)), CLASSIC, 1, 1000, ENEMY);
		this->m_ShootTimer = 3.f;
	}
	else
	{
		this->m_ShootTimer -= Time::GetDeltaTime();
	}
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Swarmer

Swarmer::Swarmer(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(15.f);
	this->m_Circle.setOrigin(15.f, 15.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 10;
	this->m_Hp = 10;
	this->m_Speed = 400.f;
}
Swarmer::~Swarmer()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Shielded

Shielded::Shielded(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 35;
	this->m_Hp = 35;
	this->m_Speed = 150.f;

	this->m_Shield = std::make_unique<Shield>(this->m_Position);
}
Shielded::~Shielded()
{

}

void Shielded::Update(sf::Vector2f& _playerPos, TileMap& _map)
{
	Enemy::Update(_playerPos,_map);

	this->m_Shield->Udpate(this->m_Active, this->m_Position, Tools::RadToDeg(Tools::VectorToAngle(this->m_Target - this->m_Position)));
}

void Shielded::Display(Window& _window)
{
	Enemy::Display(_window);
	this->m_Shield->Display(_window);
}


#pragma endregion
////////////////////////////////////////////////////////
#pragma region RangedShielded

RangedShielded::RangedShielded(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 150.f;
}
RangedShielded::~RangedShielded()
{

}

#pragma endregion
#pragma endregion
////////////////////////////////////////////////////////
#pragma region EnemyList

EnemyList::EnemyList()
{
	this->m_List.clear();
}
EnemyList::~EnemyList()
{
	this->m_List.clear();
}

void EnemyList::Clear()
{
	this->m_List.clear();
}

bool EnemyList::AllDead()
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		if (enemy->GetHP() > 0)
		{
			return false;
		}
	}
	return true;
}

void EnemyList::Update(sf::Vector2f& _playerPos, TileMap& _map)
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		enemy->Update(_playerPos, _map);
	}
}
void EnemyList::Display(Window& _window)
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		enemy->Display(_window);
	}
}

void EnemyList::Activate()
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		enemy->SetActive(true);
	}
}
void EnemyList::Respawn()
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		enemy->Respawn();
	}
}

#pragma endregion
////////////////////////////////////////////////////////