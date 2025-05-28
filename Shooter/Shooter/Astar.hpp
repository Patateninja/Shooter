#pragma once
#include "Tile.hpp"

class Node
{
	private :
		std::shared_ptr<Node> m_Prev = nullptr;
		std::shared_ptr<Tile> m_Tile = nullptr;
		int m_Gcost = 0;
		int m_Hcost = 0;
		int m_Fcost = 0;

	public :
		Node() = default;
		Node(const Tile& _tile);
		Node(const Node& _node);
		~Node();

		inline const std::shared_ptr<Tile>& GetTile() const { return this->m_Tile; };
		inline const sf::Vector2f GetCood() const { return this->m_Tile->GetCood(); };
		inline const std::shared_ptr<Node> GetPrev() const { return this->m_Prev; };
		inline const int GetG() const { return this->m_Gcost; };
		inline const int GetH() const { return this->m_Hcost; };
		inline const int GetF() const { return this->m_Fcost; };

		inline void SetTile(const Tile& _tile) { this->m_Tile = std::make_shared<Tile>(_tile); };
		inline void SetPrev(const Node& _prev) { this->m_Prev = std::make_shared<Node>(_prev); };
		inline void SetPrev()                  { this->m_Prev = nullptr; };
		inline void SetF(const int& _f)        { this->m_Fcost = _f; };
		
		void CalculateAllCost(const Node& _start, const Node& _end, const TileMap& _map);

		bool operator==(const Node& _Node2) const { return this->m_Tile->GetCood() == _Node2.m_Tile->GetCood(); };
		bool operator!=(const Node& _Node2) const { return this->m_Tile->GetCood() != _Node2.m_Tile->GetCood(); };
};

namespace Astar
{
	const std::list<Tile> Neighbor(Node& _tile, TileMap& _map);

	const int HCost(const Node& _current, const Node& _end, const TileMap& _map);
	const int GCost(const Node& _current, const Node& _start, const TileMap& _map);
	const int FCost(const Node& _current, const Node& _start, const Node& _end, const TileMap& _map);

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

	void RemoveNode(std::list<Node>& _nodelist, Node& _node);

	int NodeDist(Node& _node1, Node& _node2);

	std::list<Tile> Pathfinding(Tile& _start, Tile& _end, TileMap& _map);
	void BestNode(Node& _node, std::list<Node> _list);
	std::list<Node> Astar(Tile& _start, Tile& _end, TileMap& _map);
}