#include "Player.hpp"

////////////////////////////////////////////////////////

Player::Player()
{
	this->m_Circle = sf::CircleShape(20.f);
	this->m_Circle.setOrigin(20.f, 20.f);
	this->m_Circle.setFillColor(sf::Color::Blue);
	this->m_Position = sf::Vector2f(576.f, 64.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_InputTimer = 0.f;
	this->m_Life = 3;
	this->m_CanMove = false;
	this->m_CanReload = true;
}
Player::~Player()
{

}

void Player::Update(EnemyList& _enemyList, TileMap& _map, Window& _window)
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_CanReload)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->Ready();
			_enemyList.Activate();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Load(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Load(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Load(3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Load(4);
		}
	}
	else if (this->m_CanMove)
	{
		for (std::shared_ptr<Enemy>& enemy : _enemyList.GetList())
		{
			if (enemy->GetActive() && Tools::CircleCollision(this->m_Circle.getGlobalBounds(), enemy->GetHitbox()))
			{
				this->Die();
				_enemyList.Respawn();
				return;
			}
		}

		this->m_Velocity.x = 0;
		this->m_Velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position - sf::Vector2f(0, this->m_Circle.getRadius())) - (sf::Vector2f(0,375) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.y = -375;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position + sf::Vector2f(0, this->m_Circle.getRadius())) + (sf::Vector2f(0, 375) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.y = 375;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position - sf::Vector2f(this->m_Circle.getRadius(),0)) - (sf::Vector2f(375, 0) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.x = -375;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position + sf::Vector2f(this->m_Circle.getRadius(),0)) + (sf::Vector2f(375, 0) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.x = 375;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_InputTimer > 0.75f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Shoot(this->m_Position, this->m_Velocity, _window);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->Respawn();
			_enemyList.Respawn();
		}

		
		this->m_Position+= this->m_Velocity * Time::GetDeltaTime();
	}

	this->m_Circle.setPosition(this->m_Position);
}
void Player::Display(Window& _window)
{
	_window.Draw(this->m_Circle);

	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = this->m_Position;
	lines[0].color = sf::Color::Red;
	lines[1].position = Tools::AngleToVector(200.f, Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(this->m_Position) - _window.RelativePos(sf::Mouse::getPosition())))) + this->m_Position;
	lines[1].color = sf::Color::Red;
	_window.Draw(lines);


	int pellets = 5;
	int spreading = 25;
	for (int i = 0; i < pellets; ++i)
	{
		/*sf::VertexArray proj(sf::Lines, 2);
		proj[0].position = this->m_Position;
		proj[0].color = sf::Color::Blue;

		float spread = Tools::DegToRad((spreading / 2.f) - (float(i) * float(spreading / (pellets - 1))));
		float angle = Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0, 0)) - (_window.RelativePos(this->m_Position) - _window.RelativePos(sf::Mouse::getPosition()))) + spread;
		
		proj[1].position = (Tools::AngleToVector(1000, angle) - this->m_Velocity) + this->m_Position;
		proj[1].color = sf::Color::Blue;

		_window.Draw(proj);*/
	}


	this->m_Shotgun.DisplayMagazine(_window);
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
	this->m_Position = sf::Vector2f(576.f, 64.f); //Change to stage start pos;
	this->m_CanReload = true;
	this->m_CanMove = false;
	ProjList::Clear();
	this->m_Shotgun.EmptyMagazine();
}

////////////////////////////////////////////////////////