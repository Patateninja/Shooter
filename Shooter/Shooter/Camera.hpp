#pragma once
#include "Window.hpp"
#include "Tile.hpp"

class Camera
{
	private :
		sf::Vector2f m_Target;

	public :
		Camera() = default;
		~Camera() = default;

		void Reset();

		void Update(Window& _window);

		void NewTarget(Window& _window, sf::Vector2f _pos, sf::Vector2i _mapsize);
};