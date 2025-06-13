#pragma once
#include "Icon.hpp"

class CounterIcon
{
	private :
		sf::Text m_Text;
		Icon m_Icon;
	
	public :
		CounterIcon() = default;
		CounterIcon(sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~CounterIcon() = default;

		void Update(Window& _window, int _count);
		void Display(Window& _window);
};