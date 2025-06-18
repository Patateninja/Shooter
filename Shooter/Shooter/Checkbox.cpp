#include "Checkbox.hpp"

Checkbox::Checkbox(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture, bool _active)
{
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));

	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);

	this->m_Active = _active;

	if (this->m_Active)
	{
		this->m_Rect.setTextureRect(sf::IntRect(0, 0, 75, 75));
	}
	else
	{
		this->m_Rect.setTextureRect(sf::IntRect(75, 0, 75, 75));
	}
}

void Checkbox::Update(Window& _window, bool& _bool)
{
	this->m_Active = _bool;

	if (this->Button::Update(_window))
	{
		this->m_Active = !this->m_Active;
	}

	if (this->m_Active)
	{
		this->m_Rect.setTextureRect(sf::IntRect(0, 0, 75, 75));
	}
	else
	{
		this->m_Rect.setTextureRect(sf::IntRect(75, 0, 75, 75));
	}

	_bool = this->m_Active;
}

void Checkbox::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
}