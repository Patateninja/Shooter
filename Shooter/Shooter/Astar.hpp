#pragma once
#include "Tile.hpp"

class Node;

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

namespace debug
{
	void InitID();
	int GetID();
	void IDadd();
}

class Node
{
	private :
		int ID = 0;
		Node* m_Prev = nullptr;
		std::shared_ptr<Tile> m_Tile = nullptr;
		int m_Gcost = 0;
		int m_Hcost = 0;
		int m_Fcost = 0;
	public :
		Node()
		{
			this->ID = debug::GetID();
			debug::IDadd();
		}
		Node(Tile& _tile)
		{
			this->ID = debug::GetID();
			debug::IDadd();
			this->m_Tile = std::make_shared<Tile>(_tile);
		};
		Node(const Node& _node)
		{
			this->ID = _node.ID;
			this->m_Prev = _node.m_Prev;
			this->m_Tile = std::make_shared<Tile>(*_node.m_Tile);
			this->m_Gcost = _node.m_Gcost;
			this->m_Hcost = _node.m_Hcost;
			this->m_Fcost = _node.m_Fcost;
		}
		~Node()
		{
			this->m_Tile.reset();
		};

		inline std::shared_ptr<Tile> GetTile() { return this->m_Tile; };
		inline sf::Vector2f GetCood() { return this->m_Tile->GetCood(); };
		inline Node* GetPrev() { return this->m_Prev; };
		inline int GetG() { return this->m_Gcost; };
		inline int GetH() { return this->m_Hcost; };
		inline int GetF() { return this->m_Fcost; };

		inline void SetTile(Tile& _tile) { this->m_Tile = std::make_shared<Tile>(_tile); };
		inline void SetPrev(Node* _prev) { this->m_Prev = _prev; };
		inline void SetF(int _f) { this->m_Fcost = _f; };
		inline void CalculateAllCost(Node& _start, Node& _end, TileMap& _map)
		{
			this->m_Hcost = Astar::HCost(*this, _end, _map);
			this->m_Gcost = Astar::GCost(*this, _start, _map);
			this->m_Fcost = this->m_Hcost + this->m_Gcost;
		};

		bool operator==(const Node& _Node2) const { return this->m_Tile->GetCood() == _Node2.m_Tile->GetCood(); };
		bool operator!=(const Node& _Node2) const { return this->m_Tile->GetCood() != _Node2.m_Tile->GetCood(); };
};