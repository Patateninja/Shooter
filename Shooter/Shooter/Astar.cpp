#include "Astar.hpp"

std::list<Tile*> Neighbor(Tile& _tile, TileMap& _map)
{
	std::list<Tile*> list;

	for (int i = _tile.GetCood().x != 0 ? 0 : 1; i < _tile.GetCood().x != _map.GetSize().x * Tile::GetSize() ? 3 : 2; ++i)
	{
		for (int j = _tile.GetCood().y != 0 ? 0 : 1; j < _tile.GetCood().y != _map.GetSize().y * Tile::GetSize() ? 3 : 2; ++j)
		{
			if (_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f(i * Tile::GetSize(), j * Tile::GetSize()))) != _tile)
			{
				list.push_back(&_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f(i * Tile::GetSize(), j * Tile::GetSize()))));
			}
		}
	}

	return list;
}

template<typename T>
bool NotInList(std::list<T> _list, T _element)
{
	for (T t : _list)
	{
		if (t == _element)
		{
			return false;
		}
	}
	return true;
}

int NodeDist(Node* _node1, Node* _node2)
{
	if (_node1 == nullptr || _node2 == nullptr)
	{
		return 10000000;
	}
	return Tools::Distance(_node1->GetCood(), _node2->GetCood());
}

int HCost(Node& _current, Node& _end, TileMap& _map)
{
	return Tools::Magnitude(_current.GetCood() - _end.GetCood());
}

int GCost(Node& _current, Node& _start, TileMap& _map)
{
	return Tools::Magnitude(_start.GetCood() - _current.GetCood());
}

int FCost(Node& _current, Node& _start, Node& _end, TileMap& _map)
{
	return GCost(_current, _start, _map) + HCost(_current, _end, _map);
}

std::list<Tile> Pathfinding(Tile& _start, Tile& _end, TileMap& _map)
{
	Node* start = new Node();
	start->SetTile(&_start);
	Node* end = new Node();
	end->SetTile(&_end);
	
	std::list<Node*> toCheck;
	std::list<Node*> checked;

	Node* first = start;
	toCheck.push_back(first);

	Node* current = nullptr;
	while (*current->GetTile() != _end)
	{
		Node* bestNode = new Node();
		bestNode->SetF(10000000000);
		for (Node* node : toCheck)
		{
			if (node->GetF() < bestNode->GetF())
			{
				bestNode = node;
			}
			else if (node->GetF() == bestNode->GetF())
			{
				if (node->GetH() < bestNode->GetH())
				{
					bestNode = node;
				}
				else if (node->GetH() == bestNode->GetH())
				{
					if (bool(Tools::Random(1, 0)))
					{
						bestNode = node;
					}
				}
			}
		}
		current = bestNode;
		toCheck.remove(current);
		checked.push_back(current);

		for (Tile* neighbor : Neighbor(*current->GetTile(), _map))
		{
			Node* node = new Node();
			node->SetTile(neighbor);
			if (neighbor->GetWalkable() && !NotInList(checked, node))
			{
				if (NotInList(toCheck, node) || NodeDist(current, node) < NodeDist(node->GetPrev(), node))
				{
					node->SetF(FCost(*node, *start, *end, _map));
					node->SetPrev(current);
					if (NotInList(toCheck, node))
					{ 
						toCheck.push_back(node);
					}
				}
			}
		}
	}

	std::list<Tile> path;

	current = *checked.end();
	while (current != start)
	{
		path.push_back(*current->GetTile());
		current = current->GetPrev();
	}

	return path;
}