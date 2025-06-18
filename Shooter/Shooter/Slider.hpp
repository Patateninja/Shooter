#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

class Slider
{
	private :
		sf::RectangleShape m_Bar;
		sf::RectangleShape m_Cursor;
		int m_Percentage = 0;

	public :
		Slider() = default;
		Slider(sf::Vector2f _pos, sf::Vector2f _size, int _percent);
		~Slider() = default;

		void Update(Window& _window, int& _percent);
		void Display(Window& _window);
};