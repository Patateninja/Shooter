#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"

class PopUp
{
	private :
		Button m_Button;
		sf::Text m_Text;
		sf::RectangleShape m_Rect;

	public :
		PopUp() = default;
		PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text);
		~PopUp() = default;

		void Update();
		void Display(Window& _window);
};