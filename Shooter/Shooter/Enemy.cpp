#include "Enemy.hpp"

////////////////////////////////////////////////////////

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
		this->m_Target = _playerPos;
		this->m_Velocity = Tools::Normalize(this->m_Position - this->m_Target) * 250.f;
		this->Move(_deltatime);
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

void Enemy::Move(float _deltatime)
{
	this->m_Position -= this->m_Velocity * _deltatime;
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

////////////////////////////////////////////////////////

EnemyList::EnemyList()
{
	this->m_List.clear();
}
EnemyList::~EnemyList()
{
	this->m_List.clear();
}

void EnemyList::Add(const sf::Vector2f& _startingPos)
{
	this->m_List.push_back(std::make_unique<Enemy>(_startingPos));
}
void EnemyList::Add(Enemy& _enemy)
{
	this->m_List.push_back(std::make_unique<Enemy>(_enemy));
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

////////////////////////////////////////////////////////