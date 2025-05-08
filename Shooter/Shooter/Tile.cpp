#include "Tile.hpp"

////////////////////////////////////////////////////////

Tile::Tile()
{
	this->m_Cood = sf::Vector2f(0.f, 0.f);
	this->m_Type = WALL;
	this->m_Walkable = false;
	this->m_BulletThrough = false;
}
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
Tile::~Tile()
{

}

////////////////////////////////////////////////////////

TileMap::TileMap()
{
	this->m_Size = sf::Vector2i(0, 0);
	this->m_RectRenderer = sf::RectangleShape(sf::Vector2f(64.f,64.f));
	this->m_RectRenderer.setOrigin(32.f, 32.f);
}
TileMap::TileMap(sf::Vector2i _size)
{
	this->m_Size = _size;
	this->m_RectRenderer = sf::RectangleShape(sf::Vector2f(64.f, 64.f));
	this->m_RectRenderer.setOrigin(32.f, 32.f);
}
TileMap::~TileMap()
{
	this->m_Grid.clear();
}

void TileMap::Generate()
{
	for (int i = 0; i < this->m_Size.x; ++i)
	{
		this->m_Grid.push_back(std::list<Tile>());
		for (int j = 0; j < this->m_Size.y; ++j)
		{
			if (i == 0 || i == this->m_Size.x - 1 || j == 0 || j == this->m_Size.y - 1)
			{
				this->m_Grid.back().push_back(Tile(sf::Vector2f(float(i * 64), float(j * 64)), WALL));
			}
			else
			{
				this->m_Grid.back().push_back(Tile(sf::Vector2f(float(i * 64), float(j * 64)), TileType(Tools::Random(3,0))));
			}
		}
	}
}

Tile& TileMap::GetTile(sf::Vector2i _cood)
{
	if (_cood.x <= this->m_Size.x || _cood.y <= this->m_Size.y)
	{
		for (std::list<Tile>& tilelist : this->m_Grid)
		{
			for (Tile& tile : tilelist)
			{
				if (sf::Vector2i(tile.GetCood()) == _cood / 64)
				{
					return tile;
				}
			}
		}
	}
}
Tile& TileMap::GetTile(int _x, int _y)
{
	return this->GetTile(sf::Vector2i(_x, _y));
}

void TileMap::Display(sf::RenderTexture& _rendertexture, sf::Vector2f _playerpos)
{
	for (auto tileListIt = this->m_Grid.begin(); tileListIt != this->m_Grid.end(); ++tileListIt)
	{
		for (auto tileIt = tileListIt->begin(); tileIt != tileListIt->end(); ++tileIt)
		{
			if (Tools::Distance(tileIt->GetCood(), _playerpos) < 1164)
			{
				this->m_RectRenderer.setPosition(tileIt->GetCood());
				switch (tileIt->GetType())
				{
				case WALL:
					this->m_RectRenderer.setFillColor(sf::Color::Magenta);
					break;
				case FURNITURE:
					this->m_RectRenderer.setFillColor(sf::Color::Green);
					break;
				case FLOOR:
					this->m_RectRenderer.setFillColor(sf::Color::Cyan);
					break;
				}
				_rendertexture.draw(this->m_RectRenderer);
			}
		}
	}

	_rendertexture.display();
}

////////////////////////////////////////////////////////