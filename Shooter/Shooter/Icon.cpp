#include "Icon.hpp"

////////////////////////////////////////////////////////

Icon::Icon(sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Rect.setSize(_size);
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setTexture(_texture);
	this->m_Pos = _pos;
}

void Icon::Update(Window& _window)
{
	this->m_Rect.setPosition(_window.RelativePos(this->m_Pos));
}

void Icon::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
}

////////////////////////////////////////////////////////