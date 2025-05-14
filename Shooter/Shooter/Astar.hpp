#pragma once
#include "Tile.hpp"

class Node
{
	private :
		Node* m_Prev = nullptr;
		Tile* m_Tile = nullptr;
		int m_Gcost = 0;
		int m_Hcost = 0;
		int m_Fcost = 0;
	public :
		Node() = default;
		~Node() = default;

		inline Tile* GetTile() { return this->m_Tile; };
		inline sf::Vector2f GetCood() { return this->m_Tile->GetCood() / 64.f; };
		inline Node* GetPrev() { return this->m_Prev; };
		inline int GetG() { return this->m_Gcost; };
		inline int GetH() { return this->m_Hcost; };
		inline int GetF() { return this->m_Fcost; };

		inline void SetTile(Tile* _tile) { this->m_Tile = _tile; };
		inline void SetPrev(Node* _prev) { this->m_Prev = _prev; };
		inline void SetF(int _f) { this->m_Fcost = _f; };

		bool operator==(const Node& _Node2) const { return this->m_Tile == _Node2.m_Tile; };
		bool operator!=(const Node& _Node2) const { return this->m_Tile != _Node2.m_Tile; };
};

namespace Astar
{
	std::list<Tile> Neighbor(Tile& _tile, TileMap& _map);

	template<typename T>
	bool NotInList(std::list<T> _list, T _element)
	{
		for (T& t : _list)
		{
			if (t == _element)
			{
				return false;
			}
		}
		return true;
	}

	int NodeDist(Node& _node1, Node& _node2);

	int HCost(Node& _current, Node& _end, TileMap& _map);

	int GCost(Node& _current, Node& _start, TileMap& _map);

	int FCost(Node& _current, Node& _start, Node& _end, TileMap& _map);

	std::list<Tile> Pathfinding(Tile& _start, Tile& _end, TileMap& _map);
}