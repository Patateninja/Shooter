#include "Stage.hpp"

Stage::Stage(int _num)
{
	this->m_Num = _num;
	this->GenerateMap();
	this->SpawnEnemies();
}

void Stage::GenerateMap()
{
	this->m_MapTexture.create(Tile::GetSize() * 40, Tile::GetSize() * 40);
	this->m_TileMap = TileMap(sf::Vector2i(40, 40));
	this->m_TileMap.Generate(this->m_MapTexture);
	this->m_MapSprite.setTexture(this->m_MapTexture.getTexture());
	this->m_MapSprite.setPosition(-Tile::GetSize() / 2.f, -Tile::GetSize() / 2.f);
}
void Stage::SpawnEnemies()
{
	if (this->m_Num % 3 == 0)
	{
		this->m_EnemyList.Add<Tank>(sf::Vector2f(320.f, 640.f));
		this->m_EnemyList.Add<RangedShielded>(sf::Vector2f(64.f, 640.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(384.f, 1280.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Ranged>(sf::Vector2f(1216, 832.f));
		this->m_EnemyList.Add<RangedShielded>(sf::Vector2f(576.f, 1024.f));
		this->m_EnemyList.Add<Tank>(sf::Vector2f(1344.f, 384.f));
	}
	else if (this->m_Num % 3 == 1)
	{
		this->m_EnemyList.Add<Shielded>(sf::Vector2f(1216, 832.f));
		this->m_EnemyList.Add<Baseliner>(sf::Vector2f(576.f, 1024.f));
	}
	else
	{
		this->m_EnemyList.Add<Tank>(sf::Vector2f(64.f, 640.f));
		this->m_EnemyList.Add<Swarmer>(sf::Vector2f(960.f, 1152.f));
		this->m_EnemyList.Add<Swarmer>(sf::Vector2f(1216, 832.f));
		this->m_EnemyList.Add<Tank>(sf::Vector2f(576.f, 1024.f));
	}
}

void Stage::Init()
{
	this->GenerateMap();
	this->SpawnEnemies();
}
void Stage::Update(Player& _player)
{
	this->m_EnemyList.Update(_player.GetPos(), this->m_TileMap);
	if (this->m_EnemyList.AllDead())
	{
		++this->m_Num;
		this->m_EnemyList.Clear();
		this->Init();
		_player.Respawn();
	}
}
void Stage::Display(Window& _window)
{
	_window.Draw(this->m_MapSprite);
	this->m_EnemyList.Display(_window);
}