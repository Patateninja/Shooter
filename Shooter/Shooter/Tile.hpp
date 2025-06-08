#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"
#include <list>

typedef enum TileType
{
	WALL,
	FURNITURE,
	FLOOR,
	TO_GENERATE,
} TileType;

class Tile
{
	private :
		sf::Vector2f m_Cood;
		TileType m_Type = WALL;
		static int m_Size;
		bool m_Walkable = false;
		bool m_BulletThrough = false;

	public :
		Tile() = default;
		Tile(sf::Vector2f _pos, TileType);
		Tile(const Tile& _tile);
		~Tile() = default;

		inline sf::Vector2f GetCood() const { return this->m_Cood; };
		inline bool GetWalkable() const { return this->m_Walkable; };
		inline bool GetBulletThrough() const { return this->m_BulletThrough; };
		inline TileType GetType() const { return this->m_Type; };
		inline static int GetSize() { return Tile::m_Size; };

		void SetType(TileType _type);

		bool operator==(const Tile& _tile2) const { return this->m_Cood == _tile2.m_Cood; };
		bool operator!=(const Tile& _tile2) const { return this->m_Cood != _tile2.m_Cood; };
};

class TileMap
{
	private :
		sf::Vector2i m_Size;
		std::list<Tile> m_Map;
	public :
		TileMap() = default;
		TileMap(sf::Vector2i _size);
		~TileMap();

		inline const sf::Vector2i GetSize() const { return this->m_Size; };

		void Generate(sf::RenderTexture& _rendertexture);

		Tile& GetTile(sf::Vector2i _cood);
		Tile& GetTile(int _x, int _y);
};