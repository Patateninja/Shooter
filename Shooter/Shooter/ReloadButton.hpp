#pragma once
#include "Button.hpp"

class ReloadButton : public Button
{
	private :
		sf::Text m_PopUpText;
		sf::RectangleShape m_PopUpRect;
		bool m_DisplayPopUp = false;

	public :
		ReloadButton() = default;
		ReloadButton(std::string _str, std::string _strPopUp, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~ReloadButton() = default;

		void SetPosition(Window& _window, sf::Vector2f _pos);
		void SetPopUpText(std::string _str);
		void SetPopUpTexture(std::string _texturename);

		bool Update(Window& _window) override;
		void Display(Window& _window) override;
};

