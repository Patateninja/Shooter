#include "PopUp.hpp"

PopUp::PopUp(sf::Vector2f _pos, sf::Vector2f _size, std::string _text)
{
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);

	this->m_Text = sf::Text(_text, RscMana::Get<sf::Font>("Mono"));
}
