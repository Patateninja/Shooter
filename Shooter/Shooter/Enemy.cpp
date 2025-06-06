#include "Enemy.hpp"

////////////////////////////////////////////////////////
#pragma region Enemy

Enemy::Enemy(const sf::Vector2f& _startingPos)
{
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);
}
Enemy::~Enemy()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
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
	this->m_Thread = std::thread(&Enemy::Threadlauncher,this);
}

void Enemy::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	if (this->m_Active)
	{
		if (this->m_Thread.joinable())
		{
			this->m_Thread.join();
			this->m_Thread = std::thread(&Enemy::UpdatePath, this, std::ref(_playerPos), std::ref(_map));
			this->m_Thread.detach();
		}
		if (this->m_PathUdpateCooldown <= 0.f)
		{
			this->m_SeePlayer = this->PlayerInSight(_playerPos, _map);
			this->m_PathUdpateCooldown = 1.f;
		}
		
		this->m_PathUdpateCooldown -= Time::GetDeltaTime();

		this->m_ProjectileOrigin = this->m_Position + Tools::AngleToVector(20.f, Tools::VectorToAngle(_playerPos - this->m_Position) + Tools::DegToRad(90));
		
		if (Tools::Distance(this->m_Position, _playerPos) < this->m_ActionRange && (Tools::Distance(this->m_Position, _playerPos) > this->m_AttackRange || !this->m_SeePlayer))
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

	if (this->m_Position.x < 0.f || this->m_Position.y < 0.f || this->m_Position.x > Tile::GetSize() * (_map.GetSize().x - 1) || this->m_Position.y > Tile::GetSize() * (_map.GetSize().y - 1) || this->m_Position.x != this->m_Position.x || this->m_Position.y != this->m_Position.y)
	{
		this->TakeDamage(10000);
	}
}
void Enemy::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

bool Enemy::PlayerInSight(const sf::Vector2f& _playerPos, TileMap& _map)
{
	if (Tools::Distance(_playerPos, this->m_ProjectileOrigin) - 128 < this->m_AttackRange)
	{
		for (int i = 1; i <= int(Tools::Distance(_playerPos, this->m_ProjectileOrigin)); ++i)
		{
			if (_map.GetTile(sf::Vector2i(Tools::Normalize(_playerPos - this->m_ProjectileOrigin) * float(i)) + sf::Vector2i(this->m_ProjectileOrigin)).GetType() == WALL)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}
void Enemy::UpdatePath(const sf::Vector2f& _playerPos, TileMap& _map)
{
	while (this->m_Active && Tools::Distance(this->m_Position, _playerPos) < this->m_ActionRange)
	{
		if (this->m_PathUdpateCooldown <= 0.f)
		{
			this->m_Path = Astar::Pathfinding(_map.GetTile(int(this->m_Position.x), int(this->m_Position.y)), _map.GetTile(int(_playerPos.x), int(_playerPos.y)), _map, std::ref(this->m_Active));
			this->m_PathUdpateCooldown = 1.f;
		}
	}
}
void Enemy::Move(const sf::Vector2f& _playerPos, TileMap& _map)
{
	if (!this->m_Path.empty())
	{
		this->m_Target = this->m_Path.front().GetCood();

		this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed;

		this->m_Position += this->m_Velocity * Time::GetDeltaTime();

		if (_map.GetTile(int(this->m_Position.x), int(this->m_Position.y)) == this->m_Path.front())
		{
			this->m_Path.erase(this->m_Path.begin());
		}
	}
	else if (Tools::Distance(this->m_Position, _playerPos) < Tile::GetSize() * 3)
	{
		this->m_Target = _playerPos;

		this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed;

		if (_map.GetTile(sf::Vector2i(this->m_Position + this->m_Velocity * Time::GetDeltaTime() + Tools::Normalize(this->m_Velocity) * 25.f )).GetWalkable())
		{
			this->m_Position += this->m_Velocity * Time::GetDeltaTime();
		}
	}

	this->m_Circle.setPosition(this->m_Position);
}
void Enemy::CheckDamage()
{
	for (std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == PLAYER && [&](auto _list, std::shared_ptr<Projectile>& _proj) -> bool { for (auto pr : _list) { if (proj == pr.lock()) { return false; } } return true; } (this->m_IgnoreProj, proj))
		{
			this->TakeDamage(proj);
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
		this->m_Circle.setFillColor(Color::Flamming);
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
	Level::GainXP(this->m_MaxHp);
	this->m_Circle.setFillColor(Color::Grey);
	this->m_IgnoreProj.clear();
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Enemy Types
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
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);
}
Baseliner::~Baseliner()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
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
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);
}
Tank::~Tank()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
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
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);

	this->m_ShootTimer = 0.5f;
}
Ranged::~Ranged()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
}

void Ranged::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	Enemy::Update(_playerPos, _map);

	if (this->m_Active && this->m_SeePlayer)
	{
		if (this->m_ShootTimer <= 0.f)
		{
			this->Shoot(_playerPos);
			this->m_ShootTimer = 1.5f;
		}
		else
		{
			this->m_ShootTimer -= Time::GetDeltaTime();

		}
	}
}

void Ranged::Shoot(const sf::Vector2f& _playerPos)
{
	ProjList::Add(this->m_ProjectileOrigin, Tools::AngleToVector(1000.f, Tools::VectorToAngle(_playerPos - this->m_ProjectileOrigin) + Tools::DegToRad(float(Tools::Random(5, -5)))), CLASSIC, 1, 1000, ENEMY);
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Speedster

Speedster::Speedster(const sf::Vector2f& _startingPos)
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
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);
}
Speedster::~Speedster()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
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
	this->m_Speed = 200.f;
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);

	this->m_Shield = std::make_unique<Shield>(this->m_Position);
}
Shielded::~Shielded()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
}

void Shielded::Update(const sf::Vector2f& _playerPos, TileMap& _map)
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
	this->m_AttackRange = Tile::GetSize() * 5.f;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 150.f;
	this->m_ShootTimer = 0.5f;
	this->m_Thread = std::thread(&Enemy::Threadlauncher, this);

	this->m_Shield = std::make_unique<Shield>(this->m_Position);
}
RangedShielded::~RangedShielded()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	if (this->m_Thread.joinable())
	{
		this->m_Thread.join();
	}
}

void RangedShielded::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	Enemy::Update(_playerPos, _map);

	if (this->m_Active && this->m_SeePlayer)
	{
		if (this->m_ShootTimer <= 0.f)
		{
			this->Shoot(_playerPos);
			this->m_ShootTimer = 2.5f;
		}
		else
		{
			this->m_ShootTimer -= Time::GetDeltaTime();
		}
	}

	this->m_Shield->Udpate(this->m_Active, this->m_Position, Tools::RadToDeg(Tools::VectorToAngle(this->m_Target - this->m_Position)));
}
void RangedShielded::Display(Window& _window)
{
	Enemy::Display(_window);
	this->m_Shield->Display(_window);
}

void RangedShielded::Shoot(const sf::Vector2f& _playerPos)
{
	ProjList::Add(this->m_ProjectileOrigin, Tools::AngleToVector(1000.f, Tools::VectorToAngle(_playerPos - this->m_ProjectileOrigin) + Tools::DegToRad(float(Tools::Random(5, -5)))), CLASSIC, 1, 1000, ENEMY);
	this->m_ShootTimer = 2.5f;
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

void EnemyList::Update(const sf::Vector2f& _playerPos, TileMap& _map)
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