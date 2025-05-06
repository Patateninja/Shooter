#include "Enemy.hpp"

Enemy::Enemy()
{
	this->m_Circle = sf::CircleShape(25.f);
	this->m_Circle.setOrigin(25.f, 25.f);
	this->m_Circle.setFillColor(sf::Color::Red);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Target = sf::Vector2f(0.f, 0.f);
	this->m_Active = true;
	this->m_Hp = 20;
}
Enemy::~Enemy()
{

}

void Enemy::Update(float _deltatime, sf::Vector2f& _playerPos)
{
	if (this->m_Active)
	{
		this->Move();
		this->TakeDamage();
		this->m_Target = _playerPos;
		this->m_Velocity = Tools::Normalize(this->m_Position - this->m_Target) * 250.f;
	}
}
void Enemy::Display(Window& _window)
{
	_window.Draw(this->m_Circle);
}

void Enemy::Move()
{
	this->m_Position += this->m_Velocity;
	this->m_Circle.setPosition(this->m_Position);
}
void Enemy::TakeDamage()
{

}