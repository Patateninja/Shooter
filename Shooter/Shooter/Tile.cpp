#include "Tile.hpp"

////////////////////////////////////////////////////////

Tile::Tile()
{
	this->m_Rect = sf::RectangleShape(sf::Vector2f(64.f, 64.f));
	this->m_Position = sf::Vector2f(0.f, 0.f);
	this->m_Walkable = false;
	this->m_BulletThrough = false;
}
Tile::Tile(sf::Vector2f _pos, TileType _type)
{
	this->m_Rect = sf::RectangleShape(sf::Vector2f(64.f, 64.f));
	this->m_Rect.setPosition(_pos);
	this->m_Position = _pos;

	switch (_type)
	{
		case WALL :
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			this->m_Rect.setFillColor(sf::Color(240, 100, 80, 255));
			break;
		case FURNITURE :
			this->m_Walkable = false;
			this->m_BulletThrough = true;
			this->m_Rect.setFillColor(sf::Color(100,60,30,255));
			break;
		case FLOOR :
			this->m_Walkable = true;
			this->m_BulletThrough = true;
			this->m_Rect.setFillColor(sf::Color(180,220,200));
			break;
		default :
			this->m_Walkable = false;
			this->m_BulletThrough = false;
			this->m_Rect.setFillColor(sf::Color::Transparent);
			break;
	}
}
Tile::~Tile()
{

}

void Tile::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
}

////////////////////////////////////////////////////////

TileMap::TileMap()
{
	this->m_Size = sf::Vector2i(0, 0);
}
TileMap::TileMap(sf::Vector2i _size)
{
	this->m_Size = _size;
}
TileMap::~TileMap()
{
	this->m_Grid.clear();
}

void TileMap::Generate()
{
	for (int i = 0; i < this->m_Size.x; ++i)
	{
		for (int j = 0; j < this->m_Size.y; ++j)
		{
			if (i == 0 || i == this->m_Size.x - 1 || j == 0 || j == this->m_Size.y - 1)
			{
				this->m_Grid.push_back(Tile(sf::Vector2f(float(i * 64), float(j * 64)), WALL));
			}
			else
			{
				this->m_Grid.push_back(Tile(sf::Vector2f(float(i * 64), float(j * 64)), TileType(Tools::Random(3,0))));
			}
		}
	}
}

Tile& TileMap::GetTile(sf::Vector2i _cood)
{
	if (_cood.x <= this->m_Size.x || _cood.y <= this->m_Size.y)
	{
		for (Tile& tile : this->m_Grid)
		{
			if (sf::Vector2i(tile.GetCood()) == _cood / 64)
			{
				return tile;
			}
		}
	}
}
Tile& TileMap::GetTile(int _x, int _y)
{
	return this->GetTile(sf::Vector2i(_x, _y));
}

void TileMap::Display(Window& _window)
{
	for (Tile& tile : this->m_Grid)
	{
		tile.Display(_window);
	}
}

////////////////////////////////////////////////////////