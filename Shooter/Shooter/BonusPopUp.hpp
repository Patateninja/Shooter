#pragma once
#include "PopUp.hpp"
#include "Button.hpp"

class BonusPopUp : public PopUp
{
	private :
		Button m_CloseButton = Button::Button("OK", sf::Vector2f(), sf::Vector2f(100.f, 35.f), nullptr);
		bool m_ToDelete = false;

	public :
		BonusPopUp() = default;
		BonusPopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text, std::string _textureName);
		~BonusPopUp() = default;

		bool const GetToDelete() const { return this->m_ToDelete; }

		void Update(Window& _window) override;
		void Display(Window& _window) override;
};