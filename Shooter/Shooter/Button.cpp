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

void Button::SetPosition(sf::Vector2f _pos)
{
	this->m_Rect.setPosition(_pos);
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
}

void Button::UpdateText(std::string _str)
{
	this->m_Text.setString(_str);
}

bool Button::Clicked(Window& _window)
{
	if (!this->m_Locked && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_Rect.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))))
	{
		return true;
	}

	return false;
}

bool Button::Update(Window& _window)
{
	if (this->m_Rect.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))))
	{
		this->m_Rect.setFillColor(Color::LightGrey);
	}
	else
	{
		this->m_Rect.setFillColor(Color::Grey);
	}

	return this->Clicked(_window);
}

void Button::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
}


//////////////////////////////////////////////////