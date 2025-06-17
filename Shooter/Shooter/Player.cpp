#include "Player.hpp"

////////////////////////////////////////////////////////

Player::Player()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Position = sf::Vector2f(Tile::GetSize() * 2.f, Tile::GetSize() * 2.f);
}

void Player::Init(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock, Armor& _armor, AmmoStash& _ammoStash)
{
	this->m_Circle.setOrigin(this->m_Circle.getRadius(), this->m_Circle.getRadius());
	this->m_Circle.setFillColor(sf::Color::Blue);

	this->ModifyShotgun(_muzzle, _grip, _magazine, _stock);
	this->Equip(_armor, _ammoStash);
}

void Player::Update(EnemyList& _enemyList, TileMap& _map, Camera& _cam, Window& _window)
{
	this->m_InputTimer += Time::GetDeltaTime() * this->m_Shotgun.GetRoFMultiplier();

	if (this->m_CanReload)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->m_InputTimer > 0.3f)
		{
			if (!this->m_Shotgun.Empty())
			{
				this->m_InputTimer = 0.f;
				this->Ready();
				_enemyList.Activate();
			}
		}
	}
	else if (this->m_CanMove)
	{
		this->m_Angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(this->m_Position) - _window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))));
		this->m_Circle.setRotation(Tools::RadToDeg(this->m_Angle));

		this->m_Shotgun.ReduceRecoil();

		for (auto& enemy : _enemyList.GetList())
		{
			if (enemy.second->GetActive() && Tools::CircleCollision(this->m_Circle.getGlobalBounds(), enemy.second->GetHitbox()))
			{
				if (this->m_Vest == 0)
				{
					this->Die();
					_enemyList.Respawn(_map);
					_cam.NewTarget(_window, this->m_Position, _map.GetSize());
					return;
				}
				else
				{
					enemy.second->TakeDamage(10000);
					--this->m_Vest;
				}
			}
		}

		if (this->CheckDamage())
		{
			this->Die();
			_enemyList.Respawn(_map);
			_cam.NewTarget(_window, this->m_Position, _map.GetSize());
			return;
		}

		this->m_Velocity.x = 0;
		this->m_Velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (this->CheckWallCollision(_map,UP))
			{
				this->m_Velocity.y -= 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (this->CheckWallCollision(_map, DOWN))
			{
				this->m_Velocity.y += 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (this->CheckWallCollision(_map, LEFT))
			{
				this->m_Velocity.x -= 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (this->CheckWallCollision(_map, RIGHT))
			{
				this->m_Velocity.x += 1;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_InputTimer > 0.75f)
		{
			this->m_InputTimer = 0.f;
			if (!this->m_Shotgun.Empty())
			{
				_enemyList.AllHearSound(this->m_Position, 15);
			}
			this->m_Shotgun.Shoot(this->m_Position, this->m_Velocity, this->m_Angle, _window);
		}

		this->m_Position += Tools::AngleToVector((Tools::Magnitude(this->m_Velocity) == 0.f ? 0.f : 350.f * (this->m_Armor.GetWalkSpeedMod() * this->m_Shotgun.GetWalkSpeedMultiplier()) + int(this->m_Caffeinated) * 100), Tools::VectorToAngle(this->m_Velocity)) * Time::GetDeltaTime();
		if (Tools::Magnitude(this->m_Velocity) != 0.f)
		{
			if (RscMana::Get<sf::Sound>("Player_Step").getStatus() == sf::Sound::Stopped)
			{
				RscMana::Get<sf::Sound>("Player_Step").play();
			}
			_enemyList.AllHearSound(this->m_Position, 2);
		}
	}

	this->m_Circle.setPosition(this->m_Position);
}
void Player::Display(Window& _window)
{
	_window.Draw(this->m_Circle);

	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = this->m_Position;
	lines[0].color = sf::Color::Red;
	lines[1].position = Tools::AngleToVector(200.f, this->m_Angle) + this->m_Position;
	lines[1].color = sf::Color::Red;
	_window.Draw(lines);

	this->m_Shotgun.DisplayMagazine(_window);
}

void Player::ModifyShotgun(Muzzle& _muzzle, Grip&_grip, Magazine&_magazine, Stock& _stock)
{
	this->m_Shotgun.Modify(_muzzle, _grip, _magazine, _stock);
}
void Player::Equip(Armor& _armor, AmmoStash& _ammoStash)
{
	this->m_Armor = _armor;
	this->m_AmmoStash = _ammoStash;

	this->m_Life += this->m_Armor.GetLife();
	this->m_MaxAmmo += this->m_AmmoStash.GetCapacity();
	
	this->m_BuckShot = this->m_MaxAmmo;
	this->m_DragonBreath = this->m_MaxAmmo;
	this->m_Slug = this->m_MaxAmmo;
}

bool Player::CheckWallCollision(TileMap& _map, Direction _direction)
{
	sf::Vector2f PlayerTopRight  = this->m_Position + sf::Vector2f(-this->m_Circle.getRadius(), this->m_Circle.getRadius());
	sf::Vector2f PlayerDownRight = this->m_Position + sf::Vector2f(this->m_Circle.getRadius(), this->m_Circle.getRadius());
	sf::Vector2f PlayerTopLeft   = this->m_Position + sf::Vector2f(-this->m_Circle.getRadius(), -this->m_Circle.getRadius());
	sf::Vector2f PlayerDownLeft  = this->m_Position + sf::Vector2f(this->m_Circle.getRadius(), -this->m_Circle.getRadius());

	float velocity = 350.f * (this->m_Armor.GetWalkSpeedMod() * this->m_Shotgun.GetWalkSpeedMultiplier()) + int(this->m_Caffeinated) * 100;

	switch (_direction)
	{
		case UP :
		{
			sf::Vector2f mvt = (sf::Vector2f(0.f, -velocity) * Time::GetDeltaTime());
			if (_map.GetTile(sf::Vector2i(PlayerTopRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerTopLeft + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownLeft + mvt)).GetWalkable())
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		}
		case RIGHT :
		{
			sf::Vector2f mvt = (sf::Vector2f(velocity, 0.f) * Time::GetDeltaTime());
			if (_map.GetTile(sf::Vector2i(PlayerTopRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerTopLeft + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownLeft + mvt)).GetWalkable())
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		}
		case DOWN :
		{
			sf::Vector2f mvt = (sf::Vector2f(0.f, velocity) * Time::GetDeltaTime());
			if (_map.GetTile(sf::Vector2i(PlayerTopRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerTopLeft + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownLeft + mvt)).GetWalkable())
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		}
		case LEFT :
		{
			sf::Vector2f mvt = (sf::Vector2f(-velocity, 0.f) * Time::GetDeltaTime());
			if (_map.GetTile(sf::Vector2i(PlayerTopRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownRight + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerTopLeft + mvt)).GetWalkable() && _map.GetTile(sf::Vector2i(PlayerDownLeft + mvt)).GetWalkable())
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		}
		default :
		{
			return false;
			break;
		}
	}
}

bool Player::CheckDamage()
{
	for (const std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (this->m_Vest <= 0 && Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == ENEMY)
		{
			return true;
		}
		else if(Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == ENEMY)
		{
			proj->SetToDestroy(true);
			--this->m_Vest;
		}
	}

	return false;
}

void Player::Ready()
{
	this->m_CanMove = true;
	this->m_CanReload = false;
}
void Player::Die()
{
	--this->m_Life;
	this->Respawn();
}
void Player::Respawn()
{
	this->m_Position = sf::Vector2f(Tile::GetSize() * 2.f, Tile::GetSize() * 2.f);
	this->m_Angle = 0.f;
	this->m_CanReload = true;
	this->m_CanMove = false;

	ProjList::Clear();

	for (const std::unique_ptr<Shell>& shell : this->m_Shotgun.GetShells())
	{
		if (dynamic_cast<BuckShot*>(shell.get()))
		{
			if (this->m_BuckShot < this->m_MaxAmmo + this->m_AmmoStash.GetCapacity())
			{
				++this->m_BuckShot;
			}
		}
		else if (dynamic_cast<DragonBreath*>(shell.get()))
		{
			if (this->m_DragonBreath < this->m_MaxAmmo + this->m_AmmoStash.GetCapacity())
			{
				++this->m_DragonBreath;
			}
		}
		else if (dynamic_cast<Slug*>(shell.get()))
		{
			if (this->m_Slug < this->m_MaxAmmo + this->m_AmmoStash.GetCapacity())
			{
				++this->m_Slug;
			}
		}
	}

	this->m_Shotgun.EmptyMagazine();
}

void Player::Refill()
{
	this->m_BuckShot = this->m_MaxAmmo;
	this->m_DragonBreath = this->m_MaxAmmo;
	this->m_Slug = this->m_MaxAmmo;
}
void Player::Heal()
{
	++this->m_Life;
}
void Player::AddVest()
{
	++this->m_Vest;
}
void Player::Coffee(bool _coffee)
{
	this->m_Caffeinated = _coffee;
}
void Player::BMG50(bool _bmg)
{
	this->m_Got50BMG = _bmg;
}

////////////////////////////////////////////////////////