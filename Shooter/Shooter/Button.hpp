#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

class Button
{
	protected :
		sf::Text m_Text;
		sf::RectangleShape m_Rect;
		bool m_Locked = false;
	public :
		Button() = default;
		Button(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~Button() = default;

		bool Clicked();

		inline void Lock() { this->m_Locked = true; }
		inline void Unlock() { this->m_Locked = false; }

		virtual bool Update(int);
		virtual void Display(Window& _window);
};