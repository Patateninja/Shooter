#include "Astar.hpp"

#include <iostream>

std::list<Tile> Astar::Neighbor(Node& _node, TileMap& _map)
{
	std::list<Tile> list;

	if (_node.GetCood().x / Tile::GetSize() != 0.f)
	{
		list.push_back(_map.GetTile(sf::Vector2i(_node.GetCood() - sf::Vector2f(float(Tile::GetSize()), 0.f))));
	}
	if (_node.GetCood().x / Tile::GetSize() != Tile::GetSize() * (_map.GetSize().x - 1))
	{
		list.push_back(_map.GetTile(sf::Vector2i(_node.GetCood() + sf::Vector2f(float(Tile::GetSize()), 0.f))));
	}
	if (_node.GetCood().y / Tile::GetSize() != 0.f)
	{
		list.push_back(_map.GetTile(sf::Vector2i(_node.GetCood() - sf::Vector2f(0.f, float(Tile::GetSize())))));
	}
	if (_node.GetCood().y / Tile::GetSize() != Tile::GetSize() * (_map.GetSize().y - 1))
	{
		list.push_back(_map.GetTile(sf::Vector2i(_node.GetCood() + sf::Vector2f(0.f, float(Tile::GetSize())))));
	}

	return list;
}

void Astar::RemoveNode(std::list<Node>& _nodelist, Node& _node)
{
	for (std::list<Node>::iterator it = _nodelist.begin(); it != _nodelist.end(); ++it)
	{
		if (*it == _node)
		{
			it = _nodelist.erase(it);
			break;
		}
	}
}

int Astar::NodeDist(Node& _node1, Node& _node2)
{
	return int(Tools::Distance(_node1.GetCood(), _node2.GetCood()));
}

int Astar::HCost(Node& _current, Node& _end, TileMap& _map)
{
	return int(Tools::Distance(_current.GetCood(), _end.GetCood()));
}
int Astar::GCost(Node& _current, Node& _start, TileMap& _map)
{
	return int(Tools::Distance(_start.GetCood(), _current.GetCood()));
}
int Astar::FCost(Node& _current, Node& _start, Node& _end, TileMap& _map)
{
	return GCost(_current, _start, _map) + HCost(_current, _end, _map);
}

std::list<Tile> Astar::Pathfinding(Tile& _start, Tile& _end, TileMap& _map)
{
	std::list<Tile> path;

	if (_start == _end)
	{
		path.push_back(_end);
		return path;
	}

	Node current = Astar::Astar(_start,_end,_map).back();
	do
	{
		std::cout << "Unreaveling" << std::endl;
		path.push_front(*current.GetTile());
		current = *current.GetPrev();
	} while (*current.GetTile() != _start);

	return path;
}
void Astar::BestNode(Node& _node, std::list<Node> _list)
{
	Node bestNode;
	bestNode.SetF(int(10e12L));
	for (Node& node : _list)
	{
		std::cout << "Looking for best node" << std::endl;

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

	std::shared_ptr<Node> tmp = nullptr;
	if (bestNode.GetPrev())
	{
		tmp = bestNode.GetPrev();
	}
	_node = bestNode;
	if (tmp)
	{
		_node.SetPrev(*tmp.get());
	}
	else
	{
		_node.SetPrev();
	}
}

std::list<Node> Astar::Astar(Tile& _start, Tile& _end, TileMap& _map)
{
	debug::InitID();

	std::list<Node> toCheck;
	std::list<Node> checked;

	Node start = Node(_start);
	Node end = Node(_end);
	start.CalculateAllCost(start, end, _map);
	end.CalculateAllCost(start, end, _map);
	toCheck.push_back(start);

	Node current;
	do
	{
		std::cout << "while loop" << std::endl;

		Astar::BestNode(current, toCheck);

		Astar::RemoveNode(toCheck, current);
		
		checked.push_back(current);

		/*if (current == end)
		{
			break;
		}*/

		for (Tile& neighbor : Astar::Neighbor(current, _map))
		{
			std::cout << "neighbor loop" << std::endl;

			Node node = Node(neighbor);
			if (neighbor.GetWalkable() && Astar::NotInList(checked, node))
			{
				if (Astar::NotInList(toCheck, node) || node.GetPrev() != nullptr && (Astar::NodeDist(current, node) < Astar::NodeDist(*node.GetPrev(), node)))
				{
					node.CalculateAllCost(start, end, _map);
					node.SetPrev(current);
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

	return checked;
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