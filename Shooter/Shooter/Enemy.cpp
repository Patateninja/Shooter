#include "Enemy.hpp"

Enemy::Enemy()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Position = sf::Vector2f(100.f, 100.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_Active = true;
	this->m_Hp = 50;
}
Enemy::~Enemy()
{

}

void Enemy::Update(float _deltatime, sf::Vector2f& _playerPos)
{
	if (this->m_Active)
	{
		this->m_Target = _playerPos;
		this->m_Velocity = Tools::Normalize(this->m_Position - this->m_Target) * 250.f;
		this->Move(_deltatime);
		this->TakeDamage();
	}
}
void Enemy::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
	
	sf::Text text(std::to_string(this->m_Hp), RscMana::Get<sf::Font>("Ubuntu"));
	text.setPosition(this->m_Position);
	_window.Draw(text);
}

void Enemy::Move(float _deltatime)
{
	this->m_Position -= this->m_Velocity * _deltatime;
	this->m_Circle.setPosition(this->m_Position);

	
}
void Enemy::TakeDamage()
{
	for (std::unique_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (this->m_Circle.getGlobalBounds().intersects(proj->GetHitbox()))
		{
			this->m_Hp -= proj->GetDamage();
			proj->SetToDestroy(true);

			if (this->m_Hp <= 0)
			{
				this->m_Active = false;
				break;
			}
		}
	}
}