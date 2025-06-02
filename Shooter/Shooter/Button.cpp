#include "Button.hpp"

//////////////////////////////////////////////////

Button::Button(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);
}

bool Button::Clicked()
{
	if (!this->m_Locked && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_Rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		return true;
	}

	return false;
}

bool Button::Update(Window& _window, int _unused)
{
	if (this->m_Rect.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition())))
	{
		this->m_Rect.setFillColor(Color::LightGrey);
		this->m_Text.setFillColor(sf::Color::Blue);
	}
	else
	{
		this->m_Rect.setFillColor(Color::Grey);
	}

	return this->Clicked();
}

void Button::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
}


//////////////////////////////////////////////////