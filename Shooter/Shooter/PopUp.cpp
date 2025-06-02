#include "PopUp.hpp"

PopUp::PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text)
{
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setFillColor(Color::DarkGrey);

	this->m_Text = sf::Text(_text, RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos);

	this->m_Button = Button("X", _pos + sf::Vector2f(_size.x - 40.f, 0.f), sf::Vector2f(40.f, 40.f), &RscMana::Get<sf::Texture>("Placeholder"));
}


void PopUp::Update(Window& _window)
{
	if (this->m_Button.Update(_window,0))
	{
		this->~PopUp();
	}

	this->m_Rect.setPosition(_window.RelativePos(this->m_Rect.getPosition()));
	this->m_Text.setPosition(_window.RelativePos(this->m_Text.getPosition()));
}

void PopUp::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
	this->m_Button.Display(_window);
}