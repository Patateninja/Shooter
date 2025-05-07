#include "Enemy.hpp"

////////////////////////////////////////////////////////
#pragma region Enemy

Enemy::Enemy()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Enemy::Enemy(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Enemy::~Enemy()
{

}

void Enemy::Respawn()
{
	this->m_Position = this->m_StartingPosition;
	this->m_Circle.setPosition(this->m_StartingPosition);
	this->m_Hp = this->m_MaxHp;
	this->m_Active = false;
	this->m_Burning = false;
	this->m_BurnCoolDown = 0.f;
	this->m_BurningDamage = 0;
	this->m_Circle.setFillColor(sf::Color::Red);
}

void Enemy::Update(float _deltatime, sf::Vector2f& _playerPos)
{
	if (this->m_Active)
	{
		this->Move(_deltatime, _playerPos);
		this->CheckDamage();

		if (this->m_Burning)
		{
			this->m_BurnCoolDown -= _deltatime;
		}
		if (this->m_BurnCoolDown < 0.f)
		{
			this->TakeDamage(this->m_BurningDamage);
			this->m_BurnCoolDown = 3.f;
		}
	}
}
void Enemy::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

void Enemy::Move(float _deltatime, sf::Vector2f& _playerPos)
{
	this->m_Target = _playerPos;
	this->m_Velocity = Tools::Normalize(this->m_Target - this->m_Position) * this->m_Speed;

	this->m_Position += this->m_Velocity * _deltatime;
	this->m_Circle.setPosition(this->m_Position);
}
void Enemy::CheckDamage()
{
	for (std::unique_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (this->m_Circle.getGlobalBounds().intersects(proj->GetHitbox()))
		{
			TakeDamage(*proj);
		}
	}
}
void Enemy::TakeDamage(Projectile& _projectile)
{
	this->m_Hp -= _projectile.GetDamage();
	
	if (_projectile.GetType() != PIERCING)
	{
			_projectile.SetToDestroy(true);
	}

	if (_projectile.GetType() == FLAMMING)
	{
		this->m_Burning = true;
		this->m_BurnCoolDown = 3.f;
		this->m_BurningDamage += _projectile.GetDamage();
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
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Enemy_Types
#pragma region Baseliner

Baseliner::Baseliner()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Baseliner::Baseliner(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Baseliner::~Baseliner()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Tank

Tank::Tank()
{
	this->m_Circle = sf::CircleShape(35.f);
	this->m_Circle.setOrigin(35.f, 35.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 150;
	this->m_Hp = 150;
	this->m_Speed = 150.f;
}
Tank::Tank(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(35.f);
	this->m_Circle.setOrigin(35.f, 35.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 150;
	this->m_Hp = 150;
	this->m_Speed = 150.f;
}
Tank::~Tank()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Ranged

Ranged::Ranged()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Ranged::Ranged(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 200.f;
}
Ranged::~Ranged()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Swarmer

Swarmer::Swarmer()
{
	this->m_Circle = sf::CircleShape(15.f);
	this->m_Circle.setOrigin(15.f, 15.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 15;
	this->m_Hp = 15;
	this->m_Speed = 300.f;
}
Swarmer::Swarmer(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(15.f);
	this->m_Circle.setOrigin(15.f, 15.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 15;
	this->m_Hp = 15;
	this->m_Speed = 300.f;
}
Swarmer::~Swarmer()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Shielded

Shielded::Shielded()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 100.f;
}
Shielded::Shielded(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 100.f;
}
Shielded::~Shielded()
{

}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region RangedShielded

RangedShielded::RangedShielded()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_StartingPosition = sf::Vector2f(0.f, 0.f);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 100.f;
}
RangedShielded::RangedShielded(const sf::Vector2f& _startingPos)
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Circle.setPosition(_startingPos);
	this->m_StartingPosition = _startingPos;
	this->m_Position = _startingPos;
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_BurningDamage = 0;
	this->m_BurnCoolDown = 0.f;
	this->m_Burning = false;
	this->m_Active = false;
	this->m_MaxHp = 50;
	this->m_Hp = 50;
	this->m_Speed = 100.f;
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

void EnemyList::Update(float _deltatime, sf::Vector2f& _playerPos)
{
	for (std::shared_ptr<Enemy>& enemy : this->m_List)
	{
		enemy->Update(_deltatime, _playerPos);
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