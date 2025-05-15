#include "Astar.hpp"

#include <iostream>

std::list<Tile> Astar::Neighbor(Tile& _tile, TileMap& _map)
{
	std::list<Tile> list;

	for (int i = (_tile.GetCood().x != 0 ? 0 : 1); i < (_tile.GetCood().x != _map.GetSize().x * Tile::GetSize() ? 3 : 2); ++i)
	{
		for (int j = (_tile.GetCood().y != 0 ? 0 : 1); j < (_tile.GetCood().y != _map.GetSize().y * Tile::GetSize() ? 3 : 2); ++j)
		{
			if (_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f((i - 1) * Tile::GetSize(), (j - 1)*Tile::GetSize()))) != _tile)
			{
				list.push_back(_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f((i - 1) * Tile::GetSize(), (j - 1)*Tile::GetSize()))));
			}
		}
	}

	return list;
}

int Astar::NodeDist(Node& _node1, Node& _node2)
{
	return int(Tools::Distance(_node1.GetCood(), _node2.GetCood()));
}

int Astar::HCost(Node& _current, Node& _end, TileMap& _map)
{
	return int(Tools::Magnitude(_current.GetCood() - _end.GetCood()));
}

int Astar::GCost(Node& _current, Node& _start, TileMap& _map)
{
	return int(Tools::Magnitude(_start.GetCood() - _current.GetCood()));
}

int Astar::FCost(Node& _current, Node& _start, Node& _end, TileMap& _map)
{
	return GCost(_current, _start, _map) + HCost(_current, _end, _map);
}

std::list<Tile> Astar::Pathfinding(Tile& _start, Tile& _end, TileMap& _map)
{
	debug::InitID();

	Node start = Node(_start);
	Node end = Node(_end);
	start.CalculateAllCost(start, end, _map);
	end.CalculateAllCost(start, end, _map);
	
	std::list<Node> toCheck;
	std::list<Node> checked;

	Node first = start;
	first.SetF(Astar::FCost(start, start, end, _map));
	toCheck.push_back(first);

	Node current;
	do
	{
		std::cout << "while loop" << std::endl;

		Node bestNode;
		bestNode.SetF(10000);
		for (Node& node : toCheck)
		{
			std::cout << "node loop" << std::endl;

			if (node.GetF() < bestNode.GetF())
			{
				bestNode = node;
			}
			else if (node.GetF() == bestNode.GetF())
			{
				if (node.GetH() < bestNode.GetH())
				{
					bestNode = node;
				}
				else if (node.GetH() == bestNode.GetH())
				{
					if (bool(Tools::Random(1, 0)))
					{
						bestNode = node;
					}
				}
			}
		}
		current = Node(bestNode);
		for (std::list<Node>::iterator it = toCheck.begin(); it != toCheck.end(); ++it)
		{
			if (*it == current)
			{
				it = toCheck.erase(it);
				break;
			}
		}
		checked.push_back(current);

		if (current == end)
		{
			break;
		}

		for (Tile& neighbor : Astar::Neighbor(*current.GetTile(), _map))
		{
			std::cout << "neighbor loop" << std::endl;

			Node node = Node(neighbor);
			if (neighbor.GetWalkable() || !Astar::NotInList(checked, node))
			{
				if (Astar::NotInList(toCheck, node) || node.GetPrev() !=nullptr && (Astar::NodeDist(current, node) < Astar::NodeDist(*node.GetPrev(), node)))
				{
					node.CalculateAllCost(start, end, _map);
					node.SetPrev(new Node(current));
					if (Astar::NotInList(toCheck, node))
					{
						toCheck.push_back(node);
					}
				}
			}
		}

		std::cout << "tocheck size : " << toCheck.size() << std::endl;
		std::cout << "checked size : " << checked.size() << std::endl;

	} while (current != end);

	std::list<Tile> path;

	current = checked.back();
	while (current != start)
	{
		std::cout << "Unreaveling" << std::endl;
		path.push_back(*current.GetTile());
		current = *current.GetPrev();
	}

	return path;
}

namespace debug
{
	int id;

	void InitID()
	{
		debug::id = 0;
	}
	int GetID()
	{
		return debug::id;
	}
	void IDadd()
	{
		debug::id++;
	}
}