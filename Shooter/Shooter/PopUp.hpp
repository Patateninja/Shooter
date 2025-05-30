#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

class PopUp
{
	private :
		sf::Text m_Text;
		sf::RectangleShape m_Rect;

	public :
		PopUp() = default;
		PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text);
};