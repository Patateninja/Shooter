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
		sf::RectangleShape m_Rect;
		sf::Vector2f m_Position;
		bool m_Walkable;
		bool m_BulletThrough;
	public :
		Tile();
		Tile(sf::Vector2f _pos, TileType);
		~Tile();

		inline sf::Vector2f GetCood() { return this->m_Position; };
		inline bool GetWalkable() { return this->m_Walkable; };
		inline bool GetBulleThrough() { return this->m_BulletThrough; };

		void Display(Window& _window);
};

class TileMap
{
	private :
		sf::Vector2i m_Size;
		std::list<Tile> m_Grid;
	public :
		TileMap();
		TileMap(sf::Vector2i _size);
		~TileMap();

		void Generate();

		Tile& GetTile(sf::Vector2i _cood);
		Tile& GetTile(int _x, int _y);

		void Display(Window& _window);
};