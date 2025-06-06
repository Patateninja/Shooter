#include "Astar.hpp"

////////////////////////////////////////////////////////

Node::Node(const Tile& _tile)
{
	this->m_Tile = std::make_shared<Tile>(_tile);
}
Node::Node(const Node& _node)
{
	this->m_Prev = _node.m_Prev;
	this->m_Tile = std::make_shared<Tile>(*_node.m_Tile);
	this->m_Gcost = _node.m_Gcost;
	this->m_Hcost = _node.m_Hcost;
	this->m_Fcost = _node.m_Fcost;
}
Node::~Node()
{
	this->m_Tile.reset();
}

void Node::CalculateAllCost(const Node& _start, const Node& _end, const TileMap& _map)
{
	this->m_Hcost = Astar::HCost(*this, _end, _map);
	this->m_Gcost = Astar::GCost(*this, _start, _map);
	this->m_Fcost = this->m_Hcost + this->m_Gcost;
}

////////////////////////////////////////////////////////

const std::list<Tile> Astar::Neighbor(Node& _node, TileMap& _map)
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

const int Astar::HCost(const Node& _current, const  Node& _end, const TileMap& _map)
{
	return int(Tools::Distance(_current.GetCood(), _end.GetCood()));
}
const int Astar::GCost(const Node& _current, const Node& _start, const TileMap& _map)
{
	return int(Tools::Distance(_start.GetCood(), _current.GetCood()));
}
const int Astar::FCost(const Node& _current, const Node& _start, const Node& _end, const TileMap& _map)
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

	std::list<Node> nodeList = Astar::Astar(_start, _end, _map);

	if (!nodeList.empty())
	{
		Node current = nodeList.back();
		do
		{
			path.push_front(*current.GetTile());
			if(current.GetPrev()) 
			{
				current = *current.GetPrev();
			}

		} while (*current.GetTile() != _start);
	}

	return path;
}
void Astar::BestNode(Node& _node, std::list<Node> _list)
{
	Node bestNode;
	bestNode.SetF(int(2147483647));
	for (Node& node : _list)
	{
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
		Astar::BestNode(current, toCheck);
		Astar::RemoveNode(toCheck, current);
		checked.push_back(current);

		if (current == end || checked.size() > (_map.GetSize().x * _map.GetSize().y) / 4)
		{
			break;
		}

		for (const Tile& neighbor : Astar::Neighbor(current, _map))
		{
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

		if (!checked.empty() && toCheck.empty())
		{
			std::list<Node> still;
			still.push_back(start);
			return still;
		}

	} while (current != end);

	return checked;
}

////////////////////////////////////////////////////////