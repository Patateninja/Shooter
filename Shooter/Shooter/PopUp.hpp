#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

class PopUp
{
	protected :
		sf::Text m_Text;
		sf::RectangleShape m_Rect;
		sf::Vector2f m_Position;
		float m_Opacity = 0.f;

	public :
		PopUp() = default;
		PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text, std::string _textureName);
		~PopUp() = default;

		virtual void Update(Window& _window);
		virtual void Display(Window& _window);
};