#include "Player.hpp"

////////////////////////////////////////////////////////

Player::Player()
{
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Circle = sf::CircleShape(20.f);
	this->m_Circle.setOrigin(20.f, 20.f);
	this->m_Circle.setFillColor(sf::Color::Blue);
	this->m_Position = sf::Vector2f(576.f, 64.f);
	this->m_Velocity = sf::Vector2f(0.f, 0.f);
	this->m_MaxAmmo = 15.f;
	this->m_BuckShot = this->m_MaxAmmo;
	this->m_DragonBreath = this->m_MaxAmmo;
	this->m_Slug = this->m_MaxAmmo;
	this->m_InputTimer = 0.f;
	this->m_Life = 5;
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
			if (!this->m_Shotgun.Empty())
			{
				this->m_InputTimer = 0.f;
				this->Ready();
				_enemyList.Activate();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !this->m_Shotgun.Full() && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			this->m_Shotgun.Load(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !this->m_Shotgun.Full() && this->m_BuckShot != 0 && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			--this->m_BuckShot;
			this->m_Shotgun.Load(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !this->m_Shotgun.Full() && this->m_DragonBreath != 0 && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			--this->m_DragonBreath;
			this->m_Shotgun.Load(3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !this->m_Shotgun.Full() && this->m_Slug != 0 && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			--this->m_Slug;
			this->m_Shotgun.Load(4);
		}

		this->m_Text.setString("- Birdshot : " + this->infinite + " \n- Buckshot : " + std::to_string(this->m_BuckShot) + "\n- DragonBreath : " + std::to_string(this->m_DragonBreath) + "\n- Slug : " + std::to_string(this->m_Slug));
		this->m_Text.setPosition(_window.RelativePos(sf::Vector2f(10.f, 110.f)));
	}
	else if (this->m_CanMove)
	{
		this->m_Text.setPosition(_window.RelativePos(sf::Vector2f(10.f, 110.f)));
		this->m_Text.setString("Remaining : " + std::to_string(_enemyList.Alive()));

		for (std::shared_ptr<Enemy>& enemy : _enemyList.GetList())
		{
			if (enemy->GetActive() && Tools::CircleCollision(this->m_Circle.getGlobalBounds(), enemy->GetHitbox()))
			{
				this->Die();
				_enemyList.Respawn();
				return;
			}
		}

		if (this->CheckDamage())
		{
			this->Die();
			_enemyList.Respawn();
			return;
		}

		this->m_Velocity.x = 0;
		this->m_Velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position - sf::Vector2f(0, this->m_Circle.getRadius())) - (sf::Vector2f(0,375) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.y = -1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position + sf::Vector2f(0, this->m_Circle.getRadius())) + (sf::Vector2f(0, 375) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.y = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position - sf::Vector2f(this->m_Circle.getRadius(),0)) - (sf::Vector2f(375, 0) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.x = -1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (_map.GetTile(sf::Vector2i((this->m_Position + sf::Vector2f(this->m_Circle.getRadius(),0)) + (sf::Vector2f(375, 0) * Time::GetDeltaTime()))).GetWalkable())
			{
				this->m_Velocity.x = 1;
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

		
		this->m_Position += Tools::AngleToVector((Tools::Magnitude(this->m_Velocity) == 0.f ? 0.f : 350.f), Tools::VectorToAngle(this->m_Velocity)) * Time::GetDeltaTime();
	}

	this->m_Circle.setPosition(this->m_Position);
}
void Player::Display(Window& _window)
{
	_window.Draw(this->m_Circle);

	_window.Draw(this->m_Text);

	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = this->m_Position;
	lines[0].color = sf::Color::Red;
	lines[1].position = Tools::AngleToVector(200.f, Tools::VectorToAngle(_window.RelativePos(sf::Vector2i(0,0)) - (_window.RelativePos(this->m_Position) - _window.RelativePos(sf::Mouse::getPosition())))) + this->m_Position;
	lines[1].color = sf::Color::Red;
	_window.Draw(lines);

	this->m_Shotgun.DisplayMagazine(_window);
}

bool Player::CheckDamage()
{
	for (std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (Tools::CircleCollision(this->m_Circle.getGlobalBounds(), proj->GetHitbox()) && proj->GetTeam() == ENEMY)
		{
			return true;
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
	this->m_Position = sf::Vector2f(576.f, 64.f); //Change to stage start pos;
	this->m_CanReload = true;
	this->m_CanMove = false;
	ProjList::Clear();
	this->m_Shotgun.EmptyMagazine();
}

////////////////////////////////////////////////////////