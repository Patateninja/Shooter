#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

class Icon
{
	private :
		sf::RectangleShape m_Rect;
		sf::Vector2f m_Pos;

	public :
		Icon() = default;
		Icon(sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~Icon() = default;

		inline const sf::Vector2f GetPos() const { return this->m_Pos; }
		inline const sf::Vector2f GetSize() const { return this->m_Rect.getSize(); }

		void Update(Window& _window);

		void Display(Window& _window);
};