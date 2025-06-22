#include "CounterIcon.hpp"

////////////////////////////////////////////////////////

CounterIcon::CounterIcon(sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Icon = Icon(_pos, _size, _texture);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Pixel"));
	this->m_Text.setCharacterSize(45);
}

void CounterIcon::Update(Window& _window, int _count)
{
	this->m_Icon.Update(_window);
	this->m_Text.setString(std::to_string(_count));
	this->m_Text.setOrigin(this->m_Text.getGlobalBounds().getSize() / 2.f + this->m_Text.getLocalBounds().getPosition());
	this->m_Text.setPosition(_window.RelativePos(this->m_Icon.GetPos()) + (this->m_Icon.GetSize() / 2.f));
}

void CounterIcon::Display(Window& _window)
{
	this->m_Icon.Display(_window);
	_window.Draw(this->m_Text);
}

////////////////////////////////////////////////////////