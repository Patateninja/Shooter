#include "Stage.hpp"

Stage::Stage(int _num)
{
	this->m_Num = _num;
	this->GenerateMap();
	this->SpawnEnemies();
}
Stage::~Stage()
{
	if (this->m_Crate)
	{
		delete this->m_Crate;
	}
}

void Stage::GenerateMap()
{
	this->m_MapTexture.create(Tile::GetSize() * 40, Tile::GetSize() * 40);
	this->m_TileMap.Generate(this->m_MapTexture);
	this->m_MapSprite.setTexture(this->m_MapTexture.getTexture());
	this->m_MapSprite.setPosition(-Tile::GetSize() / 2.f, -Tile::GetSize() / 2.f);

	if (bool(Tools::Random(1, 0)))
	{
		this->m_Crate = new BonusCrate(sf::Vector2f(128.f, 128.f));
	}
	else
	{
		this->m_Crate = new BoostCrate(sf::Vector2f(128.f, 128.f),true,true);
	}
}
void Stage::SpawnEnemies()
{
	if (this->m_Num % 3 == 0)
	{
		//this->m_EnemyList.Add<Tank>(sf::Vector2f(320.f, 640.f));
		this->m_EnemyList.Add<RangedShielded>(sf::Vector2f(64.f, 640.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(384.f, 1280.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(1216.f, 832.f));
		this->m_EnemyList.Add<RangedShielded>(sf::Vector2f(576.f, 1024.f));
		//this->m_EnemyList.Add<Tank>(sf::Vector2f(1344.f, 384.f));
	}
	else if (this->m_Num % 3 == 1)
	{
		this->m_EnemyList.Add<Shielded>(sf::Vector2f(1216, 832.f));
		//this->m_EnemyList.Add<Baseliner>(sf::Vector2f(576.f, 1024.f));
	}
	else
	{
		this->m_EnemyList.Add<Tank>(sf::Vector2f(64.f, 640.f));
		this->m_EnemyList.Add<Speedster>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Speedster>(sf::Vector2f(1216, 832.f));
		this->m_EnemyList.Add<Tank>(sf::Vector2f(576.f, 1024.f));
	}
}

void Stage::Init()
{
	this->GenerateMap();
	this->SpawnEnemies();
}
void Stage::Update(Player& _player, Camera& _cam, BonusPopUp*& _popUp, Window& _window)
{
	this->m_EnemyList.Update(_player.GetPos(), this->m_TileMap);
	this->m_Crate->Update(_player, this->m_GiveCoffee, this->m_GiveBMG, this->m_GiveVest, _popUp);
	if (this->m_EnemyList.AllDead())
	{
		ProjList::Clear();
		this->m_ReadyToMoveOn = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			++this->m_Num;
			this->m_EnemyList.Clear();
			this->m_ReadyToMoveOn = false;
			delete this->m_Crate;
			this->Init();
			_player.Respawn();
			if (this->m_GiveCoffee)
			{
				_player.Coffee(true);
			}
			else
			{
				_player.Coffee(false);
			}

			if (this->m_GiveBMG)
			{
				_player.BMG50(true);
			}
			else
			{
				_player.BMG50(false);
			}

			if (this->m_GiveVest)
			{
				_player.AddVest();
			}

			this->m_GiveCoffee = false;
			this->m_GiveBMG = false;
			this->m_GiveVest = false;

			_cam.NewTarget(_window, _player.GetPos(), this->m_TileMap.GetSize());
		}
	}
}
void Stage::Display(Window& _window)
{
	_window.Draw(this->m_MapSprite);
	this->m_EnemyList.Display(_window);
	this->m_Crate->Display(_window);
}