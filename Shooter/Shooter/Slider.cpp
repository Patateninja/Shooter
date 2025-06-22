#include "Slider.hpp"

////////////////////////////////////////////////////////

Slider::Slider(sf::Vector2f _pos, sf::Vector2f _size, int _percent)
{
	this->m_Percentage = _percent;
	
	this->m_Cursor.setSize(sf::Vector2f(_size.x / 30.f, _size.y * 2.f));
	this->m_Cursor.setOrigin(this->m_Cursor.getSize() / 2.f);
	this->m_Cursor.setPosition(_pos);

	this->m_Bar.setSize(_size);
	this->m_Bar.setOrigin(0,_size.y / 2.f);
	this->m_Bar.setPosition(_pos);
}

void Slider::Update(Window& _window, int& _percent)
{
	if (this->m_Bar.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))))
	{
		this->m_Cursor.setFillColor(Color::LightGrey);
		this->m_Bar.setFillColor(Color::Grey);
	}
	else
	{
		this->m_Cursor.setFillColor(Color::Grey);
		this->m_Bar.setFillColor(Color::DarkGrey);
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_Bar.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))))
	{
		_percent = int((Tools::Distance(this->m_Bar.getPosition(), _window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))) / this->m_Bar.getGlobalBounds().width) * 100);
		RscMana::Get<sf::Sound>("ButtonClicked").play();
	}

	this->m_Percentage = _percent;
	this->m_Cursor.setPosition(this->m_Bar.getPosition().x + (this->m_Bar.getGlobalBounds().width / 100) * this->m_Percentage, this->m_Bar.getPosition().y);
}

void Slider::Display(Window& _window)
{
	_window.Draw(this->m_Bar);
	_window.Draw(this->m_Cursor);
}

////////////////////////////////////////////////////////