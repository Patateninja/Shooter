#pragma once
#include "PopUp.hpp"
#include "Button.hpp"

class BonusPopUp : public PopUp
{
	private :
		Button m_CloseButton;
		bool m_ToDelete = false;

	public :
		BonusPopUp() = default;
		BonusPopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text);
		~BonusPopUp() = default;

		bool const GetToDelete() const { return this->m_ToDelete; }

		void Update(Window& _window) override;
		void Display(Window& _window) override;
};