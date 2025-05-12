#include "Astar.hpp"

std::list<Tile> Neighbor(Tile& _tile, TileMap& _map)
{
	std::list<Tile> list;

	for (int i = _tile.GetCood().x != 0 ? 0 : 1; i < _tile.GetCood().x != _map.GetSize().x * Tile::GetSize() ? 3 : 2; ++i)
	{
		for (int j = _tile.GetCood().y != 0 ? 0 : 1; j < _tile.GetCood().y != _map.GetSize().y * Tile::GetSize() ? 3 : 2; ++j)
		{
			if (_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f(i * Tile::GetSize(), j * Tile::GetSize()))) != _tile)
			{
				list.push_back(_map.GetTile(sf::Vector2i(_tile.GetCood() + sf::Vector2f(i * Tile::GetSize(), j * Tile::GetSize()))));
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

std::list<Tile> Pathfinding(Tile& _Start, Tile& _Destination, TileMap& _map)
{
	Tile current = _Start;
	std::list<Tile> visited;
	std::list<Tile> path;

	while (current != _Destination)
	{
		Tile bestNeighbor = Tile(sf::Vector2f(-64.f, -64.f), WALL);
		for (Tile& neighbor : Neighbor(current, _map))
		{
			if (NotInList(visited, neighbor))
			{

			}
		}
	}

	return path;
}