#pragma once
#include "Window.hpp"

class Icon
{
	private :
		sf::RectangleShape m_Rect;
		sf::Vector2f m_Pos;

	public :
		Icon() = default;
		Icon(sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~Icon() = default;

		void Update(Window& _window);

		void Display(Window& _window);
};