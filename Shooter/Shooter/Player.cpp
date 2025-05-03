#include "Player.hpp"

////////////////////////////////////////////////////////

Player::Player()
{
	this->m_Circle = sf::CircleShape(37.5f);
	this->m_Circle.setOrigin(37.5f, 37.5f);
	this->m_Circle.setFillColor(sf::Color::Blue);
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_Life = 3;
	this->m_CanMove = false;
	this->m_CanReload = true;
}
Player::~Player()
{

}

void Player::Update(float _deltatime)
{

	if (this->m_CanReload)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->Ready();
		}
	}
	else if (this->m_CanMove)
	{
		if (false) //Get Hit
		{
			this->Die();
		}

		this->m_Velocity.x = 0;
		this->m_Velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			this->m_Velocity.y = 375;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->m_Velocity.y = -375;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			this->m_Velocity.x = 375;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->m_Velocity.x = -375;
		}

		this->m_Position -= this->m_Velocity * _deltatime;
	}

	this->m_Circle.setPosition(this->m_Position);
}
void Player::Display(Window& _window)
{
	_window.Draw(this->m_Circle);

	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = this->m_Position;
	lines[0].color = sf::Color::Red;
	lines[1].position = Tools::AngleToVector(200.f, Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f) - (this->m_Position - sf::Vector2f(sf::Mouse::getPosition())))) + this->m_Position;
	lines[1].color = sf::Color::Red;
	_window.Draw(lines);
}

void Player::Ready()
{
	if (true) //Shotgun Not Empty & Other Conditions
	{
		this->m_CanMove = true;
		this->m_CanReload = false;
	}
}
void Player::Die()
{
	--this->m_Life;
	this->Respawn();
}
void Player::Respawn()
{
	this->m_Position = sf::Vector2f(0.f, 0.f); //Change to stage start pos;
	this->m_CanReload = true;
	this->m_CanMove = false;
}

////////////////////////////////////////////////////////