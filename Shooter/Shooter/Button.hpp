#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"
#include <optional>

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

		void SetPosition(sf::Vector2f _pos);

		void UpdateText(std::string _str);

		bool Clicked(Window& _window);

		inline void Lock() { this->m_Locked = true; }
		inline void Unlock() { this->m_Locked = false; }

		bool Update(Window& _window);
		virtual void Display(Window& _window);
};