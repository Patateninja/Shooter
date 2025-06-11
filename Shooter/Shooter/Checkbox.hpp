#pragma once
#include "Button.hpp"

class Checkbox : public Button
{
	private :
		bool m_Active = false;

	public :
		Checkbox() = default;
		Checkbox(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture, bool _active);
		~Checkbox() = default;

		void Update(Window& _window, bool& _bool);
		void Display(Window& _window) override;
};

