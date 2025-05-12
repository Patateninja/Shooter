#pragma once
#include "Window.hpp"
#include <list>

#define TILESIZE Tile::GetSize()

typedef enum TileType
{
	WALL,
	FURNITURE,
	FLOOR,
} TileType;

class Tile
{
	private :
		sf::Vector2f m_Cood;
		TileType m_Type;
		static int m_Side;
		bool m_Walkable;
		bool m_BulletThrough;
	public :
		Tile();
		Tile(sf::Vector2f _pos, TileType);
		~Tile();

		inline sf::Vector2f GetCood() { return this->m_Cood; };
		inline bool GetWalkable() { return this->m_Walkable; };
		inline bool GetBulletThrough() { return this->m_BulletThrough; };
		inline TileType GetType() { return this->m_Type; };
		inline static int GetSize() { return Tile::m_Side; };

		bool operator==(const Tile& _tile2) const { return this->m_Cood == _tile2.m_Cood; };
		bool operator!=(const Tile& _tile2) const { return this->m_Cood != _tile2.m_Cood; };
};

class TileMap
{
	private :
		sf::RectangleShape m_RectRenderer;
		sf::Vector2i m_Size;
		std::list<Tile> m_Map;
	public :
		TileMap();
		TileMap(sf::Vector2i _size);
		~TileMap();

		inline sf::Vector2i GetSize() { return this->m_Size; };

		void Generate(sf::RenderTexture& _rendertexture);

		Tile& GetTile(sf::Vector2i _cood);
		Tile& GetTile(int _x, int _y);
};