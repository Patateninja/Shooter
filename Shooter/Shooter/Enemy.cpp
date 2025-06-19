#include "Enemy.hpp"

////////////////////////////////////////////////////////
#pragma region Enemy

Enemy::Enemy(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));
	
	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Enemy::~Enemy()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;

	if (this->m_MovingThread.joinable())
	{
		this->m_MovingThread.join();
	}
	if (this->m_PathfidingThread.joinable())
	{
		this->m_PathfidingThread.join();
	}
}

void Enemy::Respawn(TileMap& _map)
{
	this->m_Position = this->m_StartingPosition;
	this->m_Circle.setPosition(this->m_StartingPosition);
	this->m_Hp = this->m_MaxHp;
	this->m_Alive = true;
	this->m_Active = false;
	this->m_Burning = false;
	this->m_BurnCooldown = 0.f;
	this->m_BurningDamage = 0;
	this->m_ViewResetCooldown = 0.f;
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_IgnoreProj.clear();
	this->m_Path.clear();

	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_Idle = true;
	this->m_SeePlayer = false;
	this->m_CanAimPlayer = false;
	this->m_SeePlayerUdpateCooldown = 0.f;
	this->m_LosePlayerCooldown = 0.f;
	this->m_PathUdpateCooldown = 0.f;
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(this->m_StartingPosition, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->m_PathfidingThread.join();
		this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_PatrolTargets.front().GetCood(), std::ref(_map));
	}
	else if (this->m_IdleBehavior == GUARD)
	{
		this->m_PathfidingThread.join();
		this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_StartingPosition, std::ref(_map));
	}
}

void Enemy::MakePatrolPath(TileMap& _map)
{
	this->m_PatrolTargets.push_back(Tile(this->m_StartingPosition, FLOOR));
	
	Tile tile;
	int x = 10;
	do
	{
		--x;
		tile = _map.GetTile(Tools::Max<int, int, int>(0,Tools::Min<float, int, int>(this->m_Position.x + x * Tile::GetSize(), _map.GetSize().x * Tile::GetSize())), int(this->m_Position.y));
	} while (!tile.GetWalkable());
	this->m_PatrolTargets.push_back(tile);

	x = 10;
	int y = 10;
	do
	{
		--x;
		--y;
		tile = _map.GetTile(Tools::Max<int, int, int>(0, Tools::Min<float, int, int>(this->m_Position.x + x * Tile::GetSize(), _map.GetSize().x * Tile::GetSize())), Tools::Max<int, int, int>(0, Tools::Min<float, int, int>(this->m_Position.y + y * Tile::GetSize(), _map.GetSize().y * Tile::GetSize())));
	} while (!tile.GetWalkable());
	this->m_PatrolTargets.push_back(tile);

	y = 10;
	do
	{
		--y;
		tile = _map.GetTile(int(this->m_Position.x), Tools::Max<int, int, int>(0, Tools::Min<float, int, int>(this->m_Position.y + y * Tile::GetSize(), _map.GetSize().y * Tile::GetSize())));
	} while (!tile.GetWalkable());
	this->m_PatrolTargets.push_back(tile);
}

void Enemy::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	srand(unsigned int(time(nullptr)));

	if (this->m_Alive)
	{
		if (this->m_Idle)
		{
			if (this->m_IdleBehavior == PATROL)
			{
				if (_map.GetTile(sf::Vector2i(this->m_Position)).GetCood() == this->m_PatrolTargets.front().GetCood() && this->m_PathfidingThread.joinable())
				{
					this->m_PatrolTargets.push_back(this->m_PatrolTargets.front());
					this->m_PatrolTargets.erase(this->m_PatrolTargets.begin());

					this->m_PathfidingThread.join();
					this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_PatrolTargets.front().GetCood(), std::ref(_map));
				}
				if (this->m_PathUdpateCooldown > 0.f)
				{
					this->m_PathUdpateCooldown -= Time::GetDeltaTime();
				}
			}
			else if (this->m_IdleBehavior == WANDER)
			{
				if ((_map.GetTile(sf::Vector2i(this->m_Position)).GetCood() == this->m_IdleTileTarget.GetCood() && this->m_PathfidingThread.joinable()))
				{
					do
					{
						int x = Tools::Random(_map.GetSize().x - 2, 15);
						int y = Tools::Random(_map.GetSize().y - 2, 15);
						this->m_IdleTileTarget = _map.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
					} while (!this->m_IdleTileTarget.GetWalkable());

					this->m_PathfidingThread.join();
					this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_IdleTileTarget.GetCood(), std::ref(_map));
				}
				if (this->m_PathUdpateCooldown > 0.f)
				{
					this->m_PathUdpateCooldown -= Time::GetDeltaTime();
				}
			}
			else if (this->m_IdleBehavior == GUARD)
			{
				if (_map.GetTile(sf::Vector2i(this->m_Position)).GetCood() != this->m_StartingPosition)
				{
					if (this->m_PathfidingThread.joinable() && _map.GetTile(sf::Vector2i(this->m_Position)).GetCood() == this->m_StartingPosition)
					{
						this->m_PathfidingThread.join();
						this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_StartingPosition, std::ref(_map));
					}
					if (this->m_PathUdpateCooldown > 0.f)
					{
						this->m_PathUdpateCooldown -= Time::GetDeltaTime();
					}
				}
			}
		}
		else
		{
			if (this->m_PathUdpateCooldown <= 0.f && this->m_PathfidingThread.joinable() || this->m_Path.empty())
			{
				this->m_PathfidingThread.join();
				this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(_playerPos), std::ref(_map));
				this->m_PathUdpateCooldown = 1.f;
			}
			else
			{
				this->m_PathUdpateCooldown -= Time::GetDeltaTime();
			}
		}

		if (this->m_MovingThread.joinable() && ((Tools::Distance(this->m_Position, _playerPos) > this->m_AttackRange || !this->m_CanAimPlayer)))
		{
			this->m_MovingThread.join();
			this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(_playerPos), std::ref(_map));
		}
		this->m_ProjectileOrigin = this->m_Position + Tools::AngleToVector(20.f, Tools::VectorToAngle(_playerPos - this->m_Position) + Tools::DegToRad(90));

		if (this->m_Active)
		{
			if (this->m_SeePlayerUdpateCooldown <= 0.f)
			{
				this->m_CanAimPlayer = this->PlayerAimable(_playerPos, _map);
				this->m_SeePlayer = this->SeePlayer(_playerPos, _map);
				this->m_SeePlayerUdpateCooldown = 0.5f;
			}
			else
			{
				this->m_SeePlayerUdpateCooldown -= Time::GetDeltaTime();
			}

			if (this->m_CanAimPlayer || this->m_SeePlayer)
			{
				this->m_Idle = false;
				this->m_LosePlayerCooldown = 10.f;
			}
			else if (!this->m_Idle)
			{
				this->m_LosePlayerCooldown -= Time::GetDeltaTime();
			}

			if (this->m_LosePlayerCooldown < 0.f && !this->m_Idle)
			{
				this->m_Idle = true;
				this->m_SeePlayer = false;
				this->m_CanAimPlayer = false;

				if (this->m_IdleBehavior == PATROL)
				{
					this->m_PathfidingThread.join();
					this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_PatrolTargets.front().GetCood(), std::ref(_map));
				}
				else if (this->m_IdleBehavior == WANDER)
				{
					this->m_IdleTileTarget;
					do
					{
						int x = Tools::Random(_map.GetSize().x - 1, 10);
						int y = Tools::Random(_map.GetSize().y - 1, 10);
						this->m_IdleTileTarget = _map.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
					} while (!this->m_IdleTileTarget.GetWalkable());

					this->m_PathfidingThread.join();
					this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_IdleTileTarget.GetCood(), std::ref(_map));
				}
				else if (this->m_IdleBehavior == GUARD)
				{
					this->m_PathfidingThread.join();
					this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, this->m_StartingPosition, std::ref(_map));
				}
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

		if (_map.GetTile(sf::Vector2i(this->m_Position)).GetCood() == this->m_Target && !this->m_SeePlayer && this->m_Idle)
		{
			if (this->m_ViewResetCooldown <= 0.f)
			{
				this->m_Angle = this->m_DefaultAngle;
			}
			else
			{
				this->m_ViewResetCooldown -= Time::GetDeltaTime();
			}
		}
		else
		{
			this->m_ViewResetCooldown = 0.2f;
			if (this->m_SeePlayer)
			{
				this->m_Angle = Tools::RadToDeg(Tools::VectorToAngle(_playerPos - this->m_Position));
			}
			else
			{
				this->m_Angle = Tools::RadToDeg(Tools::VectorToAngle(m_Target - this->m_Position));
			}
		}

		this->m_Circle.setRotation(this->m_Angle);

		this->m_Alive = this->m_Hp > 0;

		if (this->m_Position.x <= 0.f || this->m_Position.y <= 0.f || this->m_Position.x >= Tile::GetSize() * (_map.GetSize().x - 1) || this->m_Position.y >= Tile::GetSize() * (_map.GetSize().y - 1) || this->m_Position.x != this->m_Position.x || this->m_Position.y != this->m_Position.y)
		{
			this->TakeDamage(10000);
		}
	}
}

void Enemy::Display(Window& _window)
{
	if (this->m_Alive)
	{
		sf::VertexArray fov(sf::Lines, 4);
		fov[0].position = this->m_Position;
		fov[1].position = Tools::AngleToVector(float(10 * Tile::GetSize()), Tools::DegToRad(this->m_Angle + 45.f)) + this->m_Position;
		fov[2].position = this->m_Position;
		fov[3].position = Tools::AngleToVector(float(10 * Tile::GetSize()), Tools::DegToRad(this->m_Angle - 45.f)) + this->m_Position;

		fov[0].color = Color::DarkGrey;
		fov[1].color = Color::DarkGrey;
		fov[2].color = Color::DarkGrey;
		fov[3].color = Color::DarkGrey;

		_window.Draw(fov);
	}

	_window.Draw(this->m_Circle);
}

void Enemy::HearSound(sf::Vector2f& _soundPos, int _soundIntensity)
{
	this->m_Idle = false;
	this->m_LosePlayerCooldown = 5.f;
}
bool Enemy::SeePlayer(const sf::Vector2f& _playerPos, TileMap& _map) const 
{
	if (Tools::Distance(_playerPos, this->m_Position) < 10 * Tile::GetSize())
	{
		float angle = Tools::RadToDeg(Tools::VectorToAngle(_playerPos - this->m_Position));
		if (angle < -125.f)
		{
			angle += 360.f;
		}
		if (angle > this->m_Angle - 45 && angle < this->m_Angle + 45)
		{
			for (int i = Tile::GetSize(); i <= int(Tools::Distance(_playerPos, this->m_Position)); ++i)
			{
				if (_map.GetTile(sf::Vector2i(Tools::Normalize(_playerPos - this->m_Position) * float(i)) + sf::Vector2i(this->m_Position)).GetType() == WALL)
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
bool Enemy::PlayerAimable(const sf::Vector2f& _playerPos, TileMap& _map)
{
	if (Tools::Distance(_playerPos, this->m_ProjectileOrigin) - 2 * Tile::GetSize() < this->m_AttackRange)
	{
		float angle = Tools::RadToDeg(Tools::VectorToAngle(_playerPos - this->m_Position));
		if (angle > this->m_Angle - 45 && angle < this->m_Angle + 45)
		{
			for (int i = Tile::GetSize(); i <= int(Tools::Distance(_playerPos, this->m_ProjectileOrigin)); ++i)
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
	}
	else
	{
		return false;
	}

	return true;
}

void Enemy::UpdatePath(const sf::Vector2f& _playerPos, TileMap& _map)
{
	this->m_Mutex.lock();
	this->m_Path = Astar::Pathfinding(_map.GetTile(int(this->m_Position.x), int(this->m_Position.y)), _map.GetTile(int(_playerPos.x), int(_playerPos.y)), _map, this->m_Alive);
	this->m_Mutex.unlock();
}
void Enemy::Move(const sf::Vector2f& _playerPos, TileMap& _map)
{
	this->m_Mutex.lock();
	if (this->m_Alive && !this->m_Path.empty())
	{
		try
		{
			this->m_Target = this->m_Path.front().GetCood();
		}
		catch (std::exception)
		{
			std::cerr << "Empty path" << std::endl;
		}
		this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed * (this->m_Idle ? 0.5f : 1);
		this->m_Position += this->m_Velocity * Time::GetDeltaTime();
		if ( _map.GetTile(int(this->m_Position.x), int(this->m_Position.y)) == this->m_Path.front())
		{
			this->m_Path.erase(this->m_Path.begin());
		}
	}
	else if (this->m_Alive && Tools::Distance(this->m_Position, _playerPos) < Tile::GetSize() * 2)
	{
		this->m_Target = _playerPos;

		this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed * (this->m_Idle ? 0.5f : 1);

		if (_map.GetTile(sf::Vector2i((this->m_Position + this->m_Velocity * Time::GetDeltaTime() * (this->m_Idle ? 0.5f : 1)) + (Tools::Normalize(this->m_Velocity) * 25.f))).GetWalkable())
		{
			this->m_Position += this->m_Velocity * Time::GetDeltaTime();
		}

		this->m_PathUdpateCooldown = 0.f;
	}

	this->m_Circle.setPosition(this->m_Position);
	this->m_Mutex.unlock();
}

void Enemy::CheckDamage()
{
	for (std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == PLAYER && [&](auto _list, std::shared_ptr<Projectile>& _proj) -> bool { for (decltype(auto) pr : _list) { if (proj == pr.lock()) { return false; } } return true; } (this->m_IgnoreProj, proj))
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
	this->m_SeePlayer = false;
	this->m_CanAimPlayer = false;
	this->m_Idle = true;
	Level::GainXP(this->m_MaxHp);
	this->m_Circle.setFillColor(Color::Grey);
	this->m_IgnoreProj.clear();
	RscMana::Get<sf::Sound>("Death_Enemies").play();
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Enemy Types
#pragma region Baseliner

Baseliner::Baseliner(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(50.f,50.f));
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("Baseliner"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 250.f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Baseliner::~Baseliner()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;

	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Tank

Tank::Tank(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(60.f, 60.f));
	this->m_Circle.setOrigin(30.f, 30.f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("Tank"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 125;
	this->m_Hp = 125;
	this->m_Speed = 200.f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Tank::~Tank()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;

	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Ranged

Ranged::Ranged(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(50.f, 50.f));;
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("Ranged"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_AttackRange = Tile::GetSize() * 7.f;
	this->m_MaxHp = 45;
	this->m_Hp = 45;
	this->m_Speed = 250.f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_ShootTimer = 0.5f;

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Ranged::~Ranged()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	
	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

void Ranged::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	this->Enemy::Update(_playerPos, _map);

	if (this->m_Active && this->m_CanAimPlayer)
	{
		if (this->m_ShootTimer <= 0.f)
		{
			this->Shoot(_playerPos);
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
	RscMana::Get<sf::Sound>("EnemyShot").play();
	this->m_ShootTimer = 1.5f;
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Speedster

Speedster::Speedster(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(45.f, 45.f));;
	this->m_Circle.setOrigin(22.5f, 22.5f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("Dog"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 20;
	this->m_Hp = 20;
	this->m_Speed = 400.f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Speedster::~Speedster()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	
	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

void Speedster::Die()
{
	this->m_Active = false;
	this->m_SeePlayer = false;
	this->m_CanAimPlayer = false;
	this->m_Idle = true;
	Level::GainXP(this->m_MaxHp);
	this->m_Circle.setFillColor(Color::Grey);
	this->m_IgnoreProj.clear();
	RscMana::Get<sf::Sound>("Death_dog").play();
}
#pragma endregion
////////////////////////////////////////////////////////
#pragma region Shielded

Shielded::Shielded(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(50.f, 50.f));;
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("Shielded"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_MaxHp = 65;
	this->m_Hp = 65;
	this->m_Speed = 200.f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_Shield = std::make_unique<Shield>(this->m_Position);

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
Shielded::~Shielded()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	
	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

void Shielded::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	this->Enemy::Update(_playerPos,_map);
	this->m_Shield->Udpate(this->m_Alive, this->m_Position, this->m_Angle);
}

void Shielded::Display(Window& _window)
{
	this->Enemy::Display(_window);
	this->m_Shield->Display(_window);
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region RangedShielded

RangedShielded::RangedShielded(const sf::Vector2f& _startingPos, TileMap& _map)
{
	this->m_Circle = sf::RectangleShape(sf::Vector2f(50.f, 50.f));;
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::White);
	this->m_Circle.setPosition(_startingPos);
	this->m_Circle.setTexture(&RscMana::Get<sf::Texture>("RangedShielded"));
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_AttackRange = Tile::GetSize() * 5.f;
	this->m_MaxHp = 55;
	this->m_Hp = 55;
	this->m_Speed = 150.f;
	this->m_ShootTimer = 0.5f;
	this->m_PathfidingThread = std::thread(&Enemy::UpdatePath, this, std::ref(this->m_StartingPosition), std::ref(_map));
	this->m_MovingThread = std::thread(&Enemy::Move, this, std::ref(this->m_StartingPosition), std::ref(_map));

	this->m_Shield = std::make_unique<Shield>(this->m_Position);

	this->m_IdleBehavior = IdleBehavior(Tools::Random(2));
	if (this->m_IdleBehavior == WANDER)
	{
		this->m_IdleTileTarget = Tile(_startingPos, FLOOR);
	}
	else if (this->m_IdleBehavior == PATROL)
	{
		this->MakePatrolPath(_map);
	}
}
RangedShielded::~RangedShielded()
{
	this->m_IgnoreProj.clear();
	this->m_Active = false;
	
	while (!this->m_MovingThread.joinable());
	this->m_MovingThread.join();
	while (!this->m_PathfidingThread.joinable());
	this->m_PathfidingThread.join();
}

void RangedShielded::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	this->Enemy::Update(_playerPos, _map);

	if (this->m_Active && this->m_CanAimPlayer)
	{
		if (this->m_ShootTimer <= 0.f)
		{
			this->Shoot(_playerPos);
		}
		else
		{
			this->m_ShootTimer -= Time::GetDeltaTime();
		}
	}

	this->m_Shield->Udpate(this->m_Alive, this->m_Position, this->m_Angle);
}
void RangedShielded::Display(Window& _window)
{
	this->Enemy::Display(_window);
	this->m_Shield->Display(_window);
}

void RangedShielded::Shoot(const sf::Vector2f& _playerPos)
{
	ProjList::Add(this->m_ProjectileOrigin, Tools::AngleToVector(1000.f, Tools::VectorToAngle(_playerPos - this->m_ProjectileOrigin) + Tools::DegToRad(float(Tools::Random(5, -5)))), CLASSIC, 1, 1000, ENEMY);
	RscMana::Get<sf::Sound>("EnemyShot").play();
	this->m_ShootTimer = 2.5f;
}

#pragma endregion
#pragma endregion
////////////////////////////////////////////////////////
#pragma region EnemyList

EnemyList::~EnemyList()
{
 	this->Clear();
}

void EnemyList::Clear()
{
	while (!m_List.empty())
	{
		if (this->m_List.front().first.joinable())
		{
			this->m_List.front().first.join();
		}
		this->m_List.front().second.reset();

		this->m_List.erase(this->m_List.begin());
	}
}

void EnemyList::Launch(const sf::Vector2f& _playerPos, TileMap& _map)
{
	for (auto& pair : this->m_List)
	{
		pair.first = std::thread(&Enemy::Update, pair.second.get(), std::ref(_playerPos), std::ref(_map));
	}
}

bool EnemyList::AllDead()
{
	for (auto& pair : this->m_List)
	{
		if (pair.second->GetHP() > 0)
		{
			return false;
		}
	}
	return true;
}

void EnemyList::Update(const sf::Vector2f& _playerPos, TileMap& _map)
{
	for (auto& pair : this->m_List)
	{
		if (pair.first.joinable())
		{
			pair.first.join();
			pair.first = std::thread(&Enemy::Update, pair.second.get(), std::ref(_playerPos), std::ref(_map));
		}
	}
}
void EnemyList::Display(Window& _window)
{
	for (auto& pair : this->m_List)
	{
		pair.second->Display(_window);
	}
}

void EnemyList::AllHearSound(sf::Vector2f& _soundPos, int _soundIntensity)
{
	for (auto& pair : this->m_List)
	{
		if (Tools::Distance(pair.second->GetPos(), _soundPos) / Tile::GetSize() < _soundIntensity)
		{
			pair.second->HearSound(_soundPos, _soundIntensity);
		}
	}
}

void EnemyList::Activate()
{
	for (auto& pair : this->m_List)
	{
		pair.second->SetActive(true);
	}
}
void EnemyList::Respawn(TileMap& _map)
{
	for (auto& pair : this->m_List)
	{
		if (pair.first.joinable())
		{
			pair.first.join();
		}
		pair.second->Respawn(_map);
	}

	this->Launch(sf::Vector2f(Tile::GetSize() * 3.f, Tile::GetSize() * 3.f), _map);
}

int EnemyList::Alive()
{
	int i = 0;
	for (auto& pair : this->m_List)
	{
		if (pair.second->GetHP() > 0)
		{
			++i;
		}
	}

	return i;
}

#pragma endregion
////////////////////////////////////////////////////////