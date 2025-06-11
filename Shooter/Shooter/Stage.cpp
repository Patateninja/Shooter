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

	if (this->m_Num % 3 == 0)
	{
		Tile tile;
		do
		{
			int x = Tools::Random(this->m_TileMap.GetSize().x - 1, 15);
			int y = Tools::Random(this->m_TileMap.GetSize().y - 1, 15);
			tile = this->m_TileMap.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
		} while (!tile.GetWalkable());

		this->m_Crate = new BonusCrate(tile.GetCood());
	}
	else if (this->m_Num % 5 == 0)
	{
		Tile tile;
		do
		{
			int x = Tools::Random(this->m_TileMap.GetSize().x - 1, 15);
			int y = Tools::Random(this->m_TileMap.GetSize().y - 1, 15);
			tile = this->m_TileMap.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
		} while (!tile.GetWalkable());

		this->m_Crate = new BoostCrate(tile.GetCood(), true, true);
	}
	else
	{
		this->m_Crate = nullptr;
	}
}
void Stage::SpawnEnemies()
{

	if (this->m_Num != 1 && this->m_Num != 42)
	{
		int credits = int(this->m_Num * 1.5f) + int(this->m_Num % 5 == 0) * 6 + 1;

		while (credits > 0 && this->m_EnemyList.Size() < 15)
		{
			Tile tile;
			do
			{
				int x = Tools::Random(this->m_TileMap.GetSize().x - 1, 5);
				int y = Tools::Random(this->m_TileMap.GetSize().y - 1, 5);
				tile = this->m_TileMap.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
			} while (!tile.GetWalkable());

			switch (Tools::Random(6, 0))
			{
				case 0:
					if (credits - 1 >= 0)
					{
						this->m_EnemyList.Add<Baseliner>(tile.GetCood(), this->m_TileMap);
						credits -= 1;
					}
					break;
				case 1:
					if (credits - 3 >= 0)
					{
						this->m_EnemyList.Add<Tank>(tile.GetCood(), this->m_TileMap);
						credits -= 3;
					}
					break;
				case 2:
					if (credits - 2 >= 0)
					{
						this->m_EnemyList.Add<Speedster>(tile.GetCood(), this->m_TileMap);
						credits -= 2;
					}
					break;
				case 3:
					if (credits - 4 >= 0)
					{
						this->m_EnemyList.Add<Ranged>(tile.GetCood(), this->m_TileMap);
						credits -= 4;
					}
					break;
				case 4:
					if (credits - 6 >= 0)
					{
						this->m_EnemyList.Add<Shielded>(tile.GetCood(), this->m_TileMap);
						credits -= 6;
					}
					break;
				case 5:
					if (credits - 10 >= 0)
					{
						this->m_EnemyList.Add<RangedShielded>(tile.GetCood(), this->m_TileMap);
						credits -= 10;
					}
					break;
				default:
					break;
			}
		}
	}
	else if (this->m_Num == 1)
	{

		Tile tile;
		do
		{
			int x = Tools::Random(20, 10);
			int y = Tools::Random(20, 10);
			tile = this->m_TileMap.GetTile(x * Tile::GetSize(), y * Tile::GetSize());
		} while (!tile.GetWalkable());

		this->m_EnemyList.Add<Baseliner>(tile.GetCood(), this->m_TileMap);
	}
	else
	{
		//BOSS
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
	
	if (this->m_Crate)
	{
		this->m_Crate->Update(_player, this->m_GiveCoffee, this->m_GiveBMG, this->m_GiveVest, _popUp);
	}
	
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
	if (this->m_Crate)
	{
		this->m_Crate->Display(_window);
	}
	this->m_EnemyList.Display(_window);
}