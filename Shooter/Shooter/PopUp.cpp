#include "PopUp.hpp"

////////////////////////////////////////////////////////

PopUp::PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text, std::string _textureName)
{
	this->m_Position = _pos;
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setFillColor(Color::DarkGrey);
	this->m_Rect.setFillColor(sf::Color(255, 255, 255, 0));
	this->m_Rect.setTexture(&RscMana::Get<sf::Texture>(_textureName));

	this->m_Text = sf::Text(_text, RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos);
	this->m_Text.setFillColor(sf::Color(255, 255, 255, 0));
}


void PopUp::Update(Window& _window)
{
	if (this->m_Opacity < 100.f)
	{
		this->m_Opacity += Time::GetDeltaTime() * 200.f;
	}
	if (this->m_Opacity > 100.f)
	{
		this->m_Opacity = 100;
	}

	this->m_Rect.setPosition(_window.RelativePos(this->m_Position));
	this->m_Text.setPosition(_window.RelativePos(this->m_Position));

	this->m_Rect.setFillColor(sf::Color(255, 255, 255, (this->m_Opacity / 100.f) * 255));
	this->m_Text.setFillColor(sf::Color(255, 255, 255, (this->m_Opacity / 100.f) * 255));
}

void PopUp::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
}

////////////////////////////////////////////////////////