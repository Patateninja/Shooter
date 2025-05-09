#pragma once
#include "Window.hpp"
#include <list>

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
		bool m_Walkable;
		bool m_BulletThrough;
	public :
		Tile();
		Tile(sf::Vector2f _pos, TileType);
		~Tile();

		inline sf::Vector2f GetCood() { return this->m_Cood; };
		inline bool GetWalkable() { return this->m_Walkable; };
		inline bool GetBulleThrough() { return this->m_BulletThrough; };
		inline TileType GetType() { return this->m_Type; };
};

class TileMap
{
	private :
		sf::RectangleShape m_RectRenderer;
		sf::Vector2i m_Size;
		std::list<std::list<Tile>> m_Grid;
	public :
		TileMap();
		TileMap(sf::Vector2i _size);
		~TileMap();

		void Generate(sf::RenderTexture& _rendertexture);

		Tile& GetTile(sf::Vector2i _cood);
		Tile& GetTile(int _x, int _y);
};