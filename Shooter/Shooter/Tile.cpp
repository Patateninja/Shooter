#include "Tile.hpp"

////////////////////////////////////////////////////////

int Tile::m_Side = 64;

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
Tile::Tile(const Tile& _tile)
{
	this->m_Cood = _tile.m_Cood;
	this->m_Type = _tile.m_Type;
	this->m_Walkable = _tile.m_Walkable;
	this->m_BulletThrough = _tile.m_BulletThrough;
}
Tile::~Tile()
{

}

////////////////////////////////////////////////////////

TileMap::TileMap()
{
	this->m_Size = sf::Vector2i(0, 0);
	this->m_RectRenderer = sf::RectangleShape(sf::Vector2f(float(Tile::GetSize()), float(Tile::GetSize())));
	this->m_RectRenderer.setOrigin(32.f, 32.f);
}
TileMap::TileMap(sf::Vector2i _size)
{
	this->m_Size = _size;
	this->m_RectRenderer = sf::RectangleShape(sf::Vector2f(float(Tile::GetSize()), float(Tile::GetSize())));
	this->m_RectRenderer.setOrigin(32.f, 32.f);
}
TileMap::~TileMap()
{
	this->m_Map.clear();
}

void TileMap::Generate(sf::RenderTexture& _rendertexture)
{
	for (int i = 0; i < this->m_Size.x; ++i)
	{
		for (int j = 0; j < this->m_Size.y; ++j)
		{
			if (i == 0 || i == this->m_Size.x - 1 || j == 0 || j == this->m_Size.y - 1)
			{
				this->m_Map.push_back(Tile(sf::Vector2f(float(i * Tile::GetSize()), float(j * Tile::GetSize())), WALL));
			}
			else
			{
				//this->m_Map.push_back(Tile(sf::Vector2f(float(i * Tile::GetSize()), float(j * Tile::GetSize())), TileType(Tools::Random(2, 0))));
				

				// Temp //
				if (i % 2 == 0)
				{
					this->m_Map.push_back(Tile(sf::Vector2f(float(i * Tile::GetSize()), float(j * Tile::GetSize())), TileType(Tools::Random(2, 1))));
				}
				else
				{
					this->m_Map.push_back(Tile(sf::Vector2f(float(i * Tile::GetSize()), float(j * Tile::GetSize())), FLOOR));
				}
				//////////
			}
		}
	}
	_rendertexture.clear(sf::Color::Transparent);

	for (auto tileIt = this->m_Map.begin(); tileIt != this->m_Map.end(); ++tileIt)
	{
		this->m_RectRenderer.setPosition(tileIt->GetCood() + sf::Vector2f(32.f,32.f));
		switch (tileIt->GetType())
		{
			case WALL :
				this->m_RectRenderer.setFillColor(sf::Color::Yellow);
				break;
			case FURNITURE :
				this->m_RectRenderer.setFillColor(sf::Color::Green);
				break;
			case FLOOR :
				this->m_RectRenderer.setFillColor(sf::Color::Cyan);
				break;
			default :
				m_RectRenderer.setFillColor(sf::Color::White);
				break;
		}
		_rendertexture.draw(this->m_RectRenderer);
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
}
Tile& TileMap::GetTile(int _x, int _y)
{
	return this->GetTile(sf::Vector2i(_x, _y));
}

////////////////////////////////////////////////////////