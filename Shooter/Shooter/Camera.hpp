#pragma once
#include "Window.hpp"
#include "Tile.hpp"

class Camera
{
	public :
		Camera() = default;
		~Camera() = default;

		void Update(Window& _window, sf::Vector2f _playerPos, sf::Vector2i _mapsize);
};