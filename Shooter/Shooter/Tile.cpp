#include "Tile.hpp"

////////////////////////////////////////////////////////

int Tile::m_Size = 64;

Tile::Tile(sf::Vector2f _pos, TileType _type)
{
	this->m_Type = _type;
	this->m_Cood = _pos;

	switch (_type)
	{
		case WALL :
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			break;
		case FURNITURE :
			this->m_Walkable = false;
			this->m_BulletThrough = true;
			break;
		case FLOOR :
			this->m_Walkable = true;
			this->m_BulletThrough = true;
			break;
		default :
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			break;
	}
}
Tile::Tile(const Tile& _tile)
{
	this->m_Cood = _tile.m_Cood;
	this->m_Type = _tile.m_Type;
	this->m_Walkable = _tile.m_Walkable;
	this->m_BulletThrough = _tile.m_BulletThrough;
}

void Tile::SetType(TileType _type)
{
	this->m_Type = _type;

	switch (_type)
	{
		case WALL:
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			break;
		case FURNITURE:
			this->m_Walkable = false;
			this->m_BulletThrough = true;
			break;
		case FLOOR:
			this->m_Walkable = true;
			this->m_BulletThrough = true;
			break;
		default:
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			break;
	}
}

////////////////////////////////////////////////////////

TileMap::TileMap(sf::Vector2i _size)
{
	this->m_Size = _size;
}
TileMap::~TileMap()
{
	this->m_Map.clear();
}

void TileMap::Generate(sf::RenderTexture& _rendertexture)
{
	while (!this->m_Map.empty())
	{
		this->m_Map.erase(this->m_Map.begin());
	}

	for (int i = 0; i < this->m_Size.x; ++i)
	{
		for (int j = 0; j < this->m_Size.y; ++j)
		{
			this->m_Map.push_back(Tile(sf::Vector2f(float(i * Tile::GetSize()), float(j * Tile::GetSize())), TO_GENERATE));
		}
	}

	for (Tile& tile : this->m_Map)
	{
		if (tile.GetCood().x == 0 || tile.GetCood().x == (this->m_Size.x - 1) * Tile::GetSize() || tile.GetCood().y == 0 || tile.GetCood().y == (this->m_Size.y - 1) * Tile::GetSize())
		{
			tile.SetType(WALL);
		}
		else if (tile.GetType() == TO_GENERATE)
		{
			int	x = Tools::Random(Tools::Min<int, float, int>(15, this->m_Size.x - (tile.GetCood().x / Tile::GetSize())), Tools::Min<int, float, int>(5, this->m_Size.x - (tile.GetCood().x / Tile::GetSize())));
			int y = Tools::Random(Tools::Min<int, float, int>(15, this->m_Size.y - (tile.GetCood().y / Tile::GetSize())), Tools::Min<int, float, int>(5, this->m_Size.y - (tile.GetCood().y / Tile::GetSize())));

			for (int i = 0; i < x; ++i)
			{
				for (int j = 0; j < y; ++j)
				{
					if ((i == x-1 || j == y-1) && ((i != int(x / 2)) ^! (j != int(y / 2))))
					{
						this->GetTile(int(tile.GetCood().x) + (i * Tile::GetSize()), int(tile.GetCood().y) + (j * Tile::GetSize())).SetType(WALL);
					}
					else if (i > 1 && j > 1 && i < x-2 && j < y-2 && Tools::Random(10,0) == 1)
					{
						this->GetTile(int(tile.GetCood().x) + (i * Tile::GetSize()), int(tile.GetCood().y) + (j * Tile::GetSize())).SetType(FURNITURE);
					}
					else
					{
						this->GetTile(int(tile.GetCood().x) + (i * Tile::GetSize()), int(tile.GetCood().y) + (j * Tile::GetSize())).SetType(FLOOR);
					}
				}
			}
		}
	}

	_rendertexture.clear(sf::Color::Transparent);
	sf::RectangleShape renderer = sf::RectangleShape(sf::Vector2f(float(Tile::GetSize()), float(Tile::GetSize())));
	renderer.setOrigin(32.f, 32.f);
	for (Tile& tile : this->m_Map)
	{
		renderer.setPosition(tile.GetCood() + sf::Vector2f(32.f,32.f));
		switch (tile.GetType())
		{
			case WALL :
				renderer.setFillColor(Color::Wall);
				break;
			case FURNITURE :
				renderer.setFillColor(Color::Furniture);
				break;
			case FLOOR :
				renderer.setFillColor(Color::Flooring);
				break;
			default :
				renderer.setFillColor(sf::Color::White);
				break;
		}
		_rendertexture.draw(renderer);
	}

	_rendertexture.display();
}

Tile& TileMap::GetTile(sf::Vector2i _cood)
{
	sf::Vector2i ajustedCood(Tools::ToClosestMultiple(_cood.x, Tile::GetSize()), Tools::ToClosestMultiple(_cood.y, Tile::GetSize()));

	if (ajustedCood.x <= this->m_Size.x * Tile::GetSize() && ajustedCood.y <= this->m_Size.y * Tile::GetSize())
	{
		for (Tile& tile : this->m_Map)
		{
			if (sf::Vector2i(tile.GetCood()) == ajustedCood)
			{
				return tile;
			}
		}
	}

	return this->GetTile(0, 0);
}
Tile& TileMap::GetTile(int _x, int _y)
{
	return this->GetTile(sf::Vector2i(_x, _y));
}

////////////////////////////////////////////////////////