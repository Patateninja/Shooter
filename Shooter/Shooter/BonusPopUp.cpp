#include "BonusPopUp.hpp"

BonusPopUp::BonusPopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text)
{
	this->m_Position = _pos;
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setFillColor(Color::DarkGrey);

	this->m_Text = sf::Text(_text, RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos);
	this->m_CloseButton = Button::Button("OK", _pos + (_size / 2.f), sf::Vector2f(100.f, 35.f), nullptr);
}

void BonusPopUp::Update(Window& _window)
{
	this->m_Rect.setPosition(_window.RelativePos(this->m_Position));
	this->m_Text.setPosition(_window.RelativePos(this->m_Position));
	this->m_CloseButton.SetPosition(_window.RelativePos(this->m_Position + (this->m_Rect.getSize() / 2.f)));

	if (this->m_ToDelete)
	{
		this->m_Rect.setFillColor(sf::Color::Red);
	}

	if (this->m_CloseButton.Update(_window))
	{
		this->m_ToDelete = true;
	}
}

void BonusPopUp::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
	this->m_CloseButton.Display(_window);
}